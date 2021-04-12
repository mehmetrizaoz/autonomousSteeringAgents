#include "agent.h"
#include <iostream>

using namespace std;

pvector *agent::calculateNormal(pvector *v){
   normal->x = v->x / v->magnitude();
   normal->y = v->y / v->magnitude();
   return normal;
}

pvector *agent::calculateDirection(int x, int y){
   direction->x = x - this->position->x;
   direction->y = y - this->position->y;
   return direction;
}

agent::agent(float x, float y){
    position     = new pvector(x, y);
    velocity     = new pvector(0.5, 0.5);
    acceleration = new pvector(0.0, 0.0);
    direction    = new pvector(0.0, 0.0);
    normal       = new pvector(0.0, 0.0);
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