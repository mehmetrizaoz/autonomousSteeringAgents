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
    maxForce = 0.08;
    maxSpeed = 0.5;
    r = 6;
};

void agent::setAcceleration(float x, float y){
    acceleration->x = x;
    acceleration->y = y;
}

void agent::setAcceleration(pvector *v){
    acceleration->x = v->x;
    acceleration->y = v->y;
}

void agent::setVelocity(float x, float y){
    velocity->x = x;
    velocity->y = y;
}

void agent::setPosition(float x, float y){
    position->x = x;
    position->y = y;
}

