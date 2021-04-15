#include "agent.h"
#include <iostream>

using namespace std;

agent::agent(float x, float y, float s, float f, float r, float m){
    position     = pvector(x, y);
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

void agent::updatePosition(){   
   velocity = velocity + acceleration; 
   velocity.limit(maxSpeed);
   position = position + velocity;
   acceleration = pvector(0,0);   
}

void agent::applyForce(){
   steering.div(mass);
   acceleration = acceleration + steering;
}

