#include "steeringBehavior.h"
#include "pvector.h"
#include "agent.h"
#include "path.h"
#include "point.h"
#include <vector>
#include "graphics.h"
#include "math.h"
#include <iostream>
#include <GL/glut.h>

#define CIRCLE_DISTANCE 0.1
#define CIRCLE_RADIUS   0.4

#define PI 3.14159265

using namespace std;

void steeringBehavior::setAngle(pvector &p, float angle){   
   p.x = cos ( angle * PI / 180.0 );
   p.y = sin ( angle * PI / 180.0 );
}

pvector steeringBehavior::wander(agent &agent){        
   pvector p{0, 1};
   pvector circleCenter = agent.velocity;
   circleCenter.normalize();
   circleCenter.mul(CIRCLE_DISTANCE + CIRCLE_RADIUS);  
    
   //graphics::drawPoint(point(agent.position.x + circleCenter.x, agent.position.y + circleCenter.y ));
   //graphics::drawLine(agent.position, agent.position + circleCenter);
   //point center = point(agent.position.x + circleCenter.x, circleCenter.y + agent.position.y);
   //graphics::drawCircle(center, CIRCLE_RADIUS);

   int wanderAngle = (rand() % 360);      
   pvector displacement {0, 1};      
   setAngle(displacement, wanderAngle);
   displacement.mul(CIRCLE_RADIUS);

   //graphics::drawLine(point (agent.position.x + circleCenter.x, circleCenter.y + agent.position.y),
   //                     point (agent.position.x + displacement.x + circleCenter.x, 
   //                            agent.position.y + displacement.y + circleCenter.y));
      
   agent.desiredVelocity = displacement + circleCenter;
   //graphics::drawLine(point(agent.position.x, agent.position.y),
   //                     point(agent.position.x + agent.desiredVelocity.x, agent.desiredVelocity.y + agent.position.y));

   agent.steering = agent.desiredVelocity - agent.velocity;   
      
   //move it to the center when it is out of screen
   if(agent.position.x > WIDTH || agent.position.x < -WIDTH ||
      agent.position.y > HEIGHT || agent.position.y < -HEIGHT)
      agent.position = point(0,0);      

   return agent.steering;
}

pvector steeringBehavior::align(vector<agent> boids, agent &agent){
   //TODO: check code below
   float neighborDist = 20; //TODO: magic numer
   pvector sum {0,0};  
   int count = 0;     

   for(auto it = boids.begin(); it < boids.end(); it++){
      float d = (agent.position - (*it).position).magnitude();
      if( (d >0) && (d < neighborDist) ){
         sum += (*it).velocity;
         count++;
      }
   }

   if(count>0){
      sum.div(count);
      sum.normalize();
      sum.mul(agent.maxSpeed);

      agent.steering = sum - agent.velocity;   
      //agent.steering.limit(agent.maxForce);
      return agent.steering;         
   }

   return pvector(0,0);
}

pvector steeringBehavior::cohesion(vector<agent> boids, agent &agent){
   float neighborDist = 10; //TODO: magic numer
   point sum {0,0};   
   int count = 0; 

   for(auto it = boids.begin(); it < boids.end(); it++){
      float d = (agent.position - (*it).position).magnitude();
      if( (d >0) && (d < neighborDist) ){
         sum = sum + (*it).position;
         count++;
      }
   }

   if(count>0){
      sum.div(count);
      agent.targetPoint = sum;
      return seek(agent);
   }   
   return pvector(0,0);
}

pvector steeringBehavior::separation(vector<agent> agents, agent &agent){   
   float desiredSeparation = 7; //TODO: magic number
   pvector sum = pvector(0,0);
   int count = 0;   
   for(auto it = agents.begin(); it < agents.end(); it++){      
      float d = (agent.position - (*it).position).magnitude();      
      if( (d > 0) && (d < desiredSeparation) ){ 
         pvector diff = agent.position - (*it).position;
         diff.normalize();
         diff.div(d);
         sum = sum + diff;
         count++;
      }   
   }

   if(count > 0){ //TODO: implement with common utility function      
      sum.div(count);
      sum.normalize();
      sum.mul(agent.maxSpeed);
              
      agent.steering = sum - agent.velocity;   
      //agent.steering.limit(agent.maxForce);
      return agent.steering;
   } 
   return pvector(0,0);
}

//TODO: add arriving behavior
pvector steeringBehavior::seek(agent &agent){
   agent.desiredVelocity = agent.targetPoint - agent.position;
   //agent.desiredVelocity.limit(agent.maxSpeed);

   agent.steering = agent.desiredVelocity - agent.velocity;      
   //agent.steering.limit(agent.maxForce);
   return agent.steering;  
}

pvector steeringBehavior::stayInPath_2(agent &agent, path &path){     
   float worldRecord = 1000000; //TODO: magic number
   point normalPoint, predictedPos, start, end;
   pvector distance;   

   for(auto it = path.points.begin(); it < path.points.end()-1; it++){
      start = point((*it).x, (*it).y);
      end   = point((*(it+1)).x, (*(it+1)).y);
      predictedPos = agent.position + agent.velocity; 
      normalPoint = point::getNormalPoint(predictedPos, start, end);      
      if (normalPoint.x < start.x || normalPoint.x > end.x)
         normalPoint = end;

      distance = predictedPos - normalPoint;
      if (distance.magnitude() < worldRecord) {
         worldRecord = distance.magnitude();
         agent.targetPoint = normalPoint;         
      }       
   }      
   //view.drawPoint(targetPoint);
   return seek(agent);
}

//TODO: use C++11 deprecated attribute
pvector steeringBehavior::stayInPath(agent &agent, path &path){  
   point start = path.points.at(0);
   point end   = path.points.at(1);
   point predictedPos = agent.position + agent.velocity; 
   point normalPoint = point::getNormalPoint(predictedPos, start, end);
   pvector b = end - start;
   b.normalize();

   pvector distance  = predictedPos - normalPoint;
   agent.targetPoint = normalPoint  + b;
   //view.drawLine(predictedPos, normalPoint);
   //view.drawPoint(targetPoint);
    
   if(distance.magnitude() > path.width / 8)
     return seek(agent);
   return pvector(0,0);
}

pvector steeringBehavior::inFlowField(agent &agent, flowField &flow){
    //pos_x, pos_y must be non negative integer
    int pos_x = abs((int)agent.position.x) % WIDTH;
    int pos_y = abs((int)agent.position.y) % HEIGHT;    
    //TODO: modification required for non uniform fields
    return flow.getField(pos_x, pos_y);
}

pvector steeringBehavior::stayInArea(agent &agent, int turnPoint){
   if(agent.position.x >= turnPoint){
      agent.desiredVelocity = pvector( -agent.maxSpeed, agent.velocity.y );      
      agent.steering = agent.desiredVelocity - agent.velocity;   
      return agent.steering;  
   }
   else if(agent.position.x <= -turnPoint){
      agent.desiredVelocity = pvector( agent.maxSpeed, agent.velocity.y );
      agent.steering = agent.desiredVelocity - agent.velocity;            
      return agent.steering;  
   }
   else if(agent.position.y >= turnPoint){
      agent.desiredVelocity = pvector( agent.velocity.x, -agent.maxSpeed );
      agent.steering = agent.desiredVelocity - agent.velocity;         
      return agent.steering;  
   }
   else if(agent.position.y <= -turnPoint){
      agent.desiredVelocity = pvector( agent.velocity.x, agent.maxSpeed );
      agent.steering = agent.desiredVelocity - agent.velocity;      
      return agent.steering;  
   }
   return pvector(0,0);
}
