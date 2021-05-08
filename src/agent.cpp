#include "agent.h"
#include "pvector.h"
#include "graphics.h"
#include "random.h"
#include <iostream>

using namespace std;

vector<agent> agent::agents;

void agent::createAgents(){
   agent agent1 {-10.0,  0.0};
   agent1.name = "agent1";
   agent1.setFeatures(2, 2, 20, 1);
   agent::agents.push_back(agent1);
/*
   agent agent2 { 10.0,  0.0};
   agent2.name = "agent2";
   agent2.setFeatures(4, 0.1, 20, 1);
   agent::agents.push_back(agent2);*/
}

void agent::createAgentsInLine(int agentCount){
   agent tempAgent {0, 0};
   pvector location {-33, 33};
   //pvector location {0, 0};
   
   for(int i=0; i < agentCount; i++){
      tempAgent.id = i;
      tempAgent.velocity = pvector(0, 0);
      tempAgent.position.x = location.x;
      tempAgent.position.y = location.y;
      tempAgent.targetPoint = tempAgent.position;                 

      if( ((i+1) % 14) == 0){
         location.y -= 5;
         location.x  = -33;
      }
      else
         location.x += 5; 

      tempAgent.vehicleColor = color::colors.at( (i/2) % 8 );
      tempAgent.setFeatures(0.3, 0.3, 5, 1);
      agent::agents.push_back(tempAgent);
   }
}

void agent::createRandomAgents(int agentCount){
   int size = MAX_NUMBER_OF_AGENTS * 2;   
   int arr[size];
   random::createRandomArray(arr, size);
   agent tempAgent {0, 0};
   for(int i=0; i < agentCount * 2; i=i+2){
      tempAgent.position.x = arr[i]   - WIDTH;
      tempAgent.position.y = arr[i+1] - HEIGHT;
      tempAgent.vehicleColor = color::colors.at( (i/2) % 8 );
      tempAgent.setFeatures(0.4, 0.3, 5, 1);
      agent::agents.push_back(tempAgent);
   }
}

agent::agent(float x, float  y){
    position        = point(x, y);
    velocity        = pvector(0.6, 0.0);
    acceleration    = pvector(0.0, 0.0);
    steering        = pvector(0.0, 0.0);
    desiredVelocity = pvector(0.0, 0.0);
    force           = pvector(0.0, 0.0);
    targetPoint     = point(0.0, 0.0);
    vehicleColor    = color(1.0, 0.0, 0.0);
}

void agent::updatePosition(int mode, bool arrive){
    force.limit(maxForce);
    acceleration = force;     
    velocity += acceleration;

    //TODO: refactor arriving behavior
    if(arrive == true){        
        pvector diff = targetPoint - position;
        if(diff.magnitude() > r){
            velocity.limit(maxSpeed);
        }
        else{  
            velocity.limit(maxSpeed * diff.magnitude() / r);
        }
    }
    else{
        velocity.limit(maxSpeed);
    }

    position = position + velocity;
}

void agent::setFeatures(float s, float f, float r, float m){
    setMaxSpeed(s);
    setMaxForce(f);
    setR(r);
    setMass(m);
}

agent::~agent(){}

void agent::setMass(float m){
    mass = m;
}

void agent::setR(float r){
    this->r = r;
}

void agent::setMaxSpeed(float s){
    maxSpeed = s;
}

void agent::setMaxForce(float f){
    maxForce = f;
}

void agent::applyForce(){
   //acceleration = force;   
}
