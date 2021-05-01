#include "steeringBehavior.h"
#include "pvector.h"
#include "agent.h"
#include "path.h"

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
     agent.seek(WITHOUT_ARRIVING);
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
      agent.addSteeringForce(1);
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
