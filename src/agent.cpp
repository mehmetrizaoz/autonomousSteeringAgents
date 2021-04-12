#include "agent.h"
#include <iostream>

#define LIMIT 1

using namespace std;


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
};

void agent::setAcceleration(float x, float y){
    acceleration->x = x;
    acceleration->y = y;
}

void agent::limitVelocity(){
    if(velocity->x > LIMIT)
       velocity->x = LIMIT;
    if(velocity->x < -LIMIT)
       velocity->x = -LIMIT;
    if(velocity->y > LIMIT)
       velocity->y = LIMIT;
    if(velocity->y < -LIMIT)
       velocity->y = -LIMIT;
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

