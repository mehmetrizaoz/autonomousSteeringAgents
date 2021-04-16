#include "agent.h"
#include <iostream>

#define SPEED_LIMIT 1

using namespace std;

agent::agent(float x, float  y){
    position     = pvector(x, y);
    velocity     = pvector(1.5, 0.0);
    acceleration = pvector(2.0, 0.0);
    steering     = pvector(0.0, 0.0);
    desired      = pvector(0.0, 0.0);
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
   steering.div(mass);
   acceleration = acceleration + steering;
}
