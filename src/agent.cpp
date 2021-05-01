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

void agent::uniformFlow(flowField &flow){
    //pos_x, pos_y must be non negative integer
    int pos_x = abs((int)position.x) % WIDTH;
    int pos_y = abs((int)position.y) % HEIGHT;
    
    //TODO: modification required for non uniform fields
    force = force + flow.getField(pos_x, pos_y);    
}

void agent::seek(bool arriving){
   pvector diff = targetPoint - position;
   desiredVelocity = diff;
   desiredVelocity.normalize();
   desiredVelocity.mul(maxSpeed);
   
   if(arriving == true){
      if(diff.magnitude() > r) desiredVelocity.limit(maxSpeed);       
      else desiredVelocity.limit(maxSpeed * diff.magnitude() / r);       
   } 
   addSteeringForce(1);
}

void agent::simplePath(path &path){  
  point start = path.points.at(0);
  point end   = path.points.at(1);

  point predictedPos = position + velocity; 
  point normalPoint = point::getNormalPoint(predictedPos, start, end);
  pvector b = end - start;
  b.normalize();

  pvector distance  = predictedPos - normalPoint;
  targetPoint = normalPoint  + b;

  //view.drawLine(predictedPos, normalPoint);
  //view.drawPoint(targetPoint);
    
  if(distance.magnitude() > path.width / 8)
     seek(WITHOUT_ARRIVING);
}

void agent::curvedPath(path &path){     
   float worldRecord = 1000000;
   point normalPoint;
   point predictedPos;
   pvector distance;
   point start, end;

   for(auto it = path.points.begin(); it < path.points.end()-1; it++){
      start = point((*it).x, (*it).y);
      end   = point((*(it+1)).x, (*(it+1)).y);
      predictedPos = position + velocity; 
      normalPoint = point::getNormalPoint(predictedPos, start, end);      
      if (normalPoint.x < start.x || normalPoint.x > end.x)
         normalPoint = end;

      distance = predictedPos - normalPoint;
      if (distance.magnitude() < worldRecord) {
         worldRecord = distance.magnitude();
         targetPoint = normalPoint;         
      }       
   }   
   
   //view.drawPoint(targetPoint);
   seek(WITHOUT_ARRIVING);
}

void agent::cohesion(vector<agent> boids, float multiplier){
   float neighborDist = 20; //TODO: magic numer
   point sum {0,0};
   float d;
   int count = 0;

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

void agent::separation(vector<agent> agents, float multiplier){   
   float desiredSeparation = 4; //TODO: magic numer
   int count = 0;
   pvector diff {0,0};    

   for(auto it = agents.begin(); it < agents.end(); it++){
      diff = position - (*it).position ;          
      if( (diff.magnitude() >0) && (diff.magnitude() < desiredSeparation) ){
         diff.div(diff.magnitude());
         desiredVelocity = desiredVelocity + diff;
         count++;
      }   
   }
   if(count > 0){
      desiredVelocity.div(count);
      desiredVelocity.normalize();
      desiredVelocity.mul(maxSpeed);
      addSteeringForce(multiplier);       
   } 
}