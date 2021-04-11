#include "agent.h"
#include <iostream>

using namespace std;

//TODO: acceleration will be added

agent::agent(float x, float y){
    position = new pvector(x, y);
    velocity = new pvector(1.0, 0.5);
};

agent &agent::setVelocity(float x, float y){
    velocity->x = x;
    velocity->y = y;
    return *this;
}

agent &agent::setPosition(float x, float y){
    position->x = x;
    position->y = y;
    return *this;
}

pvector *agent::getPosition(){
    return position;
}

pvector *agent::getVelocity(){
    return velocity;
}