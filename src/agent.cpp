#include "agent.h"
#include "flowField.h"
#include "graphics.h"
#include <iostream>
#include "color.h"
#include <GL/glut.h> 
#include "behavior.h"

using namespace std;

class behavior;

agent::agent(float x, float  y){
    position        = point(x, y);
    velocity        = pvector(0.0, 0.0);
    acceleration    = pvector(0.0, 0.0);
    steering        = pvector(0.0, 0.0);
    desiredVelocity = pvector(0.0, 0.0);
    force           = pvector(0.0, 0.0);
    targetPoint     = point(0.0, 0.0);
    vehicleColor    = color(1.0, 0.0, 0.0);
    ccc =  behavior();
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

void agent::addSteeringForce(){
   steering = desiredVelocity - velocity;
   steering.limit(maxForce);
   force = force + steering;
}

void agent::uniformFlow(flowField &flow){
    //pos_x, pos_y must be non negative integer
    int pos_x = abs((int)position.x) % WIDTH;
    int pos_y = abs((int)position.y) % HEIGHT;
    
    //TODO: modification required for non uniform fields
    force = force + flow.getField(pos_x, pos_y);    
}

void agent::seek(){
    desiredVelocity = targetPoint - position;
    desiredVelocity.normalize();
    desiredVelocity.mul(maxSpeed);

    //arriving behavior
    if(desiredVelocity.magnitude() > r) { desiredVelocity.limit(maxSpeed); }
    else { desiredVelocity.limit(maxSpeed / 2); }
    
    addSteeringForce();
}

void agent::reflect(graphics &view, int wall, int distance){    
   view.drawWall(wall);
   int turnPoint = wall - distance; 

   if(position.x >= turnPoint){
      desiredVelocity = pvector( -maxSpeed, velocity.y );
      addSteeringForce();
   }
   else if(position.x <= -turnPoint){
      desiredVelocity = pvector( maxSpeed, velocity.y );
      addSteeringForce();
   }
   else if(position.y >= turnPoint){
      desiredVelocity = pvector( velocity.x, -maxSpeed );
      addSteeringForce();
   }
   else if(position.y <= -turnPoint){
      desiredVelocity = pvector( velocity.x, maxSpeed );
      addSteeringForce();
   }
}

void agent::simplePath(graphics &view, path &pathSimple){  
  point start = pathSimple.points.at(0);
  point end   = pathSimple.points.at(1);

  view.drawPath(pathSimple);

  point predictedPos = position + velocity; 
  point normalPoint = point::getNormalPoint(predictedPos, start, end);
  pvector b = end - start;
  b.normalize();

  pvector distance  = predictedPos - normalPoint;
  targetPoint = normalPoint  + b;

  view.drawLine(predictedPos, normalPoint);
  view.drawPoint(targetPoint);
    
  if(distance.magnitude() > pathSimple.width / 8){
     seek();
  }  
}

void agent::curvedPath(graphics &view, path &pathMultiSegment){     
   float worldRecord = 1000000;
   point normalPoint;
   point predictedPos;
   pvector distance;
   point start, end;

   view.drawPath(pathMultiSegment);

   for(auto it = pathMultiSegment.points.begin(); it < pathMultiSegment.points.end()-1; it++){
      start = point((*it).x, (*it).y);
      end   = point((*(it+1)).x, (*(it+1)).y);
      predictedPos = position + velocity; 
      normalPoint = point::getNormalPoint(predictedPos, start, end);
      
      if (normalPoint.x < start.x || normalPoint.x > end.x) {
         normalPoint = end;
      }      

      distance = predictedPos - normalPoint;
      if (distance.magnitude() < worldRecord) {
         worldRecord = distance.magnitude();
         targetPoint = normalPoint;         
      }       
   }   
   //view.drawPoint(targetPoint);
   seek();
}

void agent::cohesion(vector<agent> boids, graphics &view){
   float neighborDist = 20;
   pvector sum = pvector(0,0);
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
     targetPoint.x = sum.x;
     targetPoint.y = sum.y;
     //glColor3f( vehicleColor.R, vehicleColor.G, vehicleColor.B); 
     //view.drawPoint(targetPoint);

     desiredVelocity = targetPoint - position;
     desiredVelocity.normalize();
     desiredVelocity.mul(maxSpeed);
    
     steering = desiredVelocity - velocity;
     steering.limit(maxForce);
     steering.div(4);
     force = force + steering;
   }   
}

void agent::align(vector<agent> boids){
   float neighborDist = 15;
   pvector sum = pvector(0,0);
   float d;
   int count = 0;

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
      steering = sum - velocity;
      steering.limit(maxForce);
      force = force + steering;
   }
}

void agent::separation(vector<agent> agents){
   float desiredSeparation = 3;
   pvector sum = pvector(0,0);   
   int count = 0;
   float d = 0;
   pvector diff = pvector(0,0); 

   for(auto it = agents.begin(); it < agents.end(); it++){
      d = ( position - (*it).position ).magnitude();          
      if( (d >0) && (d < desiredSeparation) ){
         diff = position - (*it).position;         
         diff.normalize();
         diff.div(d);
         sum = sum + diff;
         count++;
      }   
   }

   if(count > 0){
      sum.div(count);
      sum.mul(maxSpeed);      
      steering = sum - velocity;
      steering.limit(maxForce);
      
      //steering.mul(0.5); // !
      force = force + steering; 
   } 
}