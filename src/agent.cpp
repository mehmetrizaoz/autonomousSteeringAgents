/**
 * @file   agent.cpp
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  implementation of the agent class
 * @date   14.05.2021
*/

#include "agent.h"
#include "pvector.h"
#include "graphics.h"
#include "random.h"
#include <iostream>

using namespace std;

agent::agent()
{

}

string agent::getName(){
   return name;
}

void agent::setName(string n){
    name = n;
}

float agent::getMass(){
   return mass;
}

void agent::setMass(float m){
    mass = m;
}

agent::agent(float x, float  y)
{
    position        = point(x, y);
    velocity        = pvector(0.6, 0.0);
    acceleration    = pvector(0.0, 0.0);
    steering        = pvector(0.0, 0.0);
    desiredVelocity = pvector(0.0, 0.0);
    force           = pvector(0.0, 0.0);
    targetPoint     = point(0.0, 0.0);
    fillColor       = color(1.0, 0.0, 0.0);
}

void agent::updatePosition(bool arrive)
{
    force.limit(maxForce);
    acceleration = force;     
    velocity += acceleration;

    //arriving behavior implementation
    if(arrive == true){        
        pvector diff = targetPoint - position;
        if(diff.magnitude() > r)
            velocity.limit(maxSpeed);        
        else
            velocity.limit(maxSpeed * diff.magnitude() / r);        
    }
    else
        velocity.limit(maxSpeed);

    position = position + velocity;
    force = pvector(0,0);
}

void agent::setFeatures(float s, float f, float r, float m)
{
    this->maxSpeed = s;
    this->maxForce = f;
    this->r = r;
    this->mass = m;
}

agent::~agent()
{
    
}
