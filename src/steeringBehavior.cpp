#include "steeringBehavior.h"
#include "pvector.h"
#include "agent.h"
#include "path.h"
#include "point.h"
#include <vector>

void steeringBehavior::cohesion(vector<agent> boids, agent &agent, float multiplier){
   float neighborDist = 20; //TODO: magic numer
   point sum {0,0};
   float d;
   int count = 0;
 
   //TODO: logic below will be function and unit test for the function will be created
   for(auto it = boids.begin(); it < boids.end(); it++){
      d = (agent.position - (*it).position).magnitude();
      if( (d >0) && (d < neighborDist) ){
         sum = sum + (*it).position;
         count++;
      }
   }

   if(count>0){
     sum.div(count);
     agent.targetPoint = sum;
     agent.desiredVelocity = agent.targetPoint - agent.position;
     agent.desiredVelocity.normalize();
     agent.desiredVelocity.mul(agent.maxSpeed);
     agent.addSteeringForce(multiplier);    
   }   
}

void steeringBehavior::separation(vector<agent> agents, agent &agent, float multiplier){   
   float desiredSeparation = 4; //TODO: magic numer
   int count = 0;
   pvector diff {0,0}; 

   //TODO: logic below will be function and unit test for the function will be created
   for(auto it = agents.begin(); it < agents.end(); it++){
      diff = agent.position - (*it).position ;          
      if( (diff.magnitude() >0) && (diff.magnitude() < desiredSeparation) ){         
         diff.div(diff.magnitude());
         agent.desiredVelocity = agent.desiredVelocity + diff;
         count++;
      }   
   }

   if(count > 0){ //TODO: implement with common utility function
      agent.desiredVelocity.div(count);
      agent.desiredVelocity.normalize();
      agent.desiredVelocity.mul(agent.maxSpeed);
      agent.addSteeringForce(multiplier);       
   } 
}

void steeringBehavior::seek(agent &agent, bool arriving){
   pvector diff = agent.targetPoint - agent.position;
   agent.desiredVelocity = diff;
   agent.desiredVelocity.normalize();
   agent.desiredVelocity.mul(agent.maxSpeed);
   
   if(arriving == true){
      if(diff.magnitude() > agent.r) agent.desiredVelocity.limit(agent.maxSpeed);       
      else agent.desiredVelocity.limit(agent.maxSpeed * diff.magnitude() / agent.r);       
   } 
   agent.addSteeringForce(1); //!
}

void steeringBehavior::stayInPath_2(agent &agent, path &path){     
   float worldRecord = 1000000; //TODO: magic number
   point normalPoint;
   point predictedPos;
   pvector distance;
   point start, end;

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
   seek(agent, WITHOUT_ARRIVING); //!
}

//TODO: use C++11 deprecated attribute
void steeringBehavior::stayInPath(agent &agent, path &path){  
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
     seek(agent, WITHOUT_ARRIVING); //!
}

void steeringBehavior::inFlowField(agent &agent, flowField &flow){
    //pos_x, pos_y must be non negative integer
    int pos_x = abs((int)agent.position.x) % WIDTH;
    int pos_y = abs((int)agent.position.y) % HEIGHT;
    
    //TODO: modification required for non uniform fields
    agent.force = agent.force + flow.getField(pos_x, pos_y);    
}

void steeringBehavior::stayInArea(agent &agent, int turnPoint){
   if(agent.position.x >= turnPoint){
      agent.desiredVelocity = pvector( -agent.maxSpeed, agent.velocity.y );
      agent.addSteeringForce(1); //!
   }
   else if(agent.position.x <= -turnPoint){
      agent.desiredVelocity = pvector( agent.maxSpeed, agent.velocity.y );
      agent.addSteeringForce(1);
   }
   else if(agent.position.y >= turnPoint){
      agent.desiredVelocity = pvector( agent.velocity.x, -agent.maxSpeed );
      agent.addSteeringForce(1);
   }
   else if(agent.position.y <= -turnPoint){
      agent.desiredVelocity = pvector( agent.velocity.x, agent.maxSpeed );
      agent.addSteeringForce(1);
   }
}
