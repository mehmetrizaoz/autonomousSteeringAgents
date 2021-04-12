#include "agent.h"
#include <iostream>

using namespace std;

//TODO: acceleration will be added

agent::agent(float x, float y){
    position     = new pvector(x, y);
    velocity     = new pvector(0.5, 0.5);
    acceleration = new pvector(0.0, 0.0);
};

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

pvector *agent::getPosition(){
    return position;
}

pvector *agent::getVelocity(){
    return velocity;
}

pvector *agent::getAcceleration(){
    return acceleration;
}

float agent::getMagnitude(pvector *v){
   return v->magnitude();
}