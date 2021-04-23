#include "agent.h"
#include "flowField.h"
#include <iostream>

using namespace std;

agent::agent(float x, float  y){
    position     = point(x, y);
    velocity     = pvector(-0.2, 0.2);
    acceleration = pvector(0.0, 0.0);
    steering     = pvector(0.0, 0.0);
    desired      = pvector(0.0, 0.0);
    force        = pvector(0.0, 0.0);
    targetPoint  = point(0.0, 0.0);
}

void agent::updatePosition(){
   velocity = velocity + acceleration;    
   velocity.limit(maxSpeed);   
   position = position + velocity;
   acceleration = pvector(0,0);  
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

void agent::applySteeringForce(){
   steering = desired - velocity;
   steering.limit(maxForce);
   force = steering;
   applyForce();
}

void agent::applyWindForce(flowField &flow){
    //pos_x, pos_y must be non negative integer
    int pos_x = abs((int)position.x) % WIDTH;
    int pos_y = abs((int)position.y) % HEIGHT;
    
    //TODO: modification required for non uniform fields
    force = flow.getField(pos_x, pos_y); 
    applyForce();
}

void agent::seekTarget(){
    desired = targetPoint - position;
    desired.normalize();
    desired.mul(maxSpeed);

    //arriving behavior
    if(desired.magnitude() > r) { desired.limit(maxSpeed); }
    else { desired.limit(maxSpeed / 2); }
    
    applySteeringForce();
}