#include "agent.h"
#include <iostream>

using namespace std;

agent::agent(float x, float y){
    position = new pvector(x, y);
    velocity = new pvector(1.0, 0.5);
};

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