#include "steeringBehavior.h"
#include "pvector.h"
#include "agent.h"

void steeringBehavior::uniformFlow(agent &agent, flowField &flow){
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
