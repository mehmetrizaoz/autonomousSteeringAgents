#include "agent.h"
#include <iostream>

#define SPEED_LIMIT 1

using namespace std;

agent::agent(float x, float y){
    position     = new pvector(x, y);
    velocity     = new pvector(0.5, 0.5);
    acceleration = new pvector(0.0, 0.0);
    steering     = new pvector(0.0, 0.0);
    desired      = new pvector(0.0, 0.0);
};

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

void agent::setAcceleration(float x, float y){
    acceleration->x = x;
    acceleration->y = y;
}

void agent::setVelocity(float x, float y){
    velocity->x = x;
    velocity->y = y;
}

void agent::setPosition(float x, float y){
    position->x = x;
    position->y = y;
}

