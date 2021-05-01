#include "agent.h"
#include "pvector.h"
#include "graphics.h"
#include <iostream>

using namespace std;

agent::agent(float x, float  y){
    position        = point(x, y);
    velocity        = pvector(0.3, 0.4);
    acceleration    = pvector(0.0, 0.0);
    steering        = pvector(0.0, 0.0);
    desiredVelocity = pvector(0.0, 0.0);
    force           = pvector(0.0, 0.0);
    targetPoint     = point(0.0, 0.0);
    vehicleColor    = color(1.0, 0.0, 0.0);
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
   acceleration = force;
   force = pvector(0,0);
}

void agent::addSteeringForce(float multiplier){
   steering = desiredVelocity - velocity;
   steering.limit(maxForce);
   steering.mul(multiplier);
   desiredVelocity = pvector(0,0);
   force = force + steering;
}

void agent::cohesion(vector<agent> boids, float multiplier){
   float neighborDist = 20; //TODO: magic numer
   point sum {0,0};
   float d;
   int count = 0;
 
   //TODO: logic below will be function and unit test for the function will be created
   for(auto it = boids.begin(); it < boids.end(); it++){
      d = (position - (*it).position).magnitude();
      if( (d >0) && (d < neighborDist) ){
         sum = sum + (*it).position;
         count++;
      }
   }

   if(count>0){
     sum.div(count);
     targetPoint = sum;
     desiredVelocity = targetPoint - position;
     desiredVelocity.normalize();
     desiredVelocity.mul(maxSpeed);
     addSteeringForce(multiplier);    
   }   
}

void agent::align(vector<agent> boids, float multiplier){
   float neighborDist = 20; //TODO: magic numer
   float d;
   int count = 0;   
   pvector sum {0,0};

   //TODO: logic below will be function and unit test for the function will be created
   for(auto it = boids.begin(); it < boids.end(); it++){
      d = (position - (*it).position).magnitude();
      if( (d >0) && (d < neighborDist) ){
         sum = sum + (*it).velocity;
         count++;
      }
   }

   if(count>0){
      sum.div(count);
      sum.normalize();
      sum.mul(maxSpeed);

      desiredVelocity = sum;
      addSteeringForce(multiplier);   
   }
}
