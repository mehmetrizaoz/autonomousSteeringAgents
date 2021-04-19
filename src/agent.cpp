#include "agent.h"
#include <iostream>

using namespace std;

agent::agent(float x, float  y){
    position     = pvector(x, y);
    velocity     = pvector(0.1, 0.05);
    acceleration = pvector(0.0, 0.0);
    steering     = pvector(0.0, 0.0);
    desired      = pvector(0.0, 0.0);
    force        = pvector(0.0, 0.0);
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
   force.div(mass);    
   acceleration = acceleration + force;
}
