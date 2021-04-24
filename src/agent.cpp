#include "agent.h"
#include "flowField.h"
#include "graphics.h"
#include <iostream>

using namespace std;

agent::agent(float x, float  y){
    position        = point(x, y);
    velocity        = pvector(0.2, 0.2);
    acceleration    = pvector(0.0, 0.0);
    steering        = pvector(0.0, 0.0);
    desiredVelocity = pvector(0.0, 0.0);
    force           = pvector(0.0, 0.0);
    targetPoint     = point(0.0, 0.0);
}

void agent::updatePosition(){
   //cout << "acc: " << acceleration.x << " " << acceleration.y << endl;
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
   //cout << "acc3 : " << acceleration.x << " " << acceleration.y << endl;
}

void agent::applySteeringForce(){
   steering = desiredVelocity - velocity;
   //cout << "steering : " << steering.x << " " << steering.y << endl;
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
    desiredVelocity = targetPoint - position;
    desiredVelocity.normalize();
    desiredVelocity.mul(maxSpeed);

    //arriving behavior
    if(desiredVelocity.magnitude() > r) { desiredVelocity.limit(maxSpeed); }
    else { desiredVelocity.limit(maxSpeed / 2); }
    
    applySteeringForce();
}

void agent::reflect(graphics &view, int wall, int distance){    
   view.drawWall(wall);
   int turnPoint = wall - distance; 

   if(position.x >= turnPoint){
      desiredVelocity = pvector( -maxSpeed, velocity.y );
      applySteeringForce();
   }
   else if(position.x <= -turnPoint){
      desiredVelocity = pvector( maxSpeed, velocity.y );
      applySteeringForce();
   }
   else if(position.y >= turnPoint){
      desiredVelocity = pvector( velocity.x, -maxSpeed );
      applySteeringForce();
   }
   else if(position.y <= -turnPoint){
      desiredVelocity = pvector( velocity.x, maxSpeed );
      applySteeringForce();
   }
}

void agent::followSimplePath(graphics &view, path &pathSimple){  
  point start = pathSimple.points.at(0);
  point end   = pathSimple.points.at(1);

  view.drawPath(start, end, pathSimple.width);

  point predictedPos = position + velocity; 
  point normalPoint = point::getNormalPoint(predictedPos, start, end);
  pvector b = end - start;
  b.normalize();

  pvector distance  = predictedPos - normalPoint;
  targetPoint = normalPoint  + b;

  view.drawLine(predictedPos, normalPoint);
  view.drawPoint(targetPoint);
    
  if(distance.magnitude() > pathSimple.width / 8){
     seekTarget();
  }  
}

void agent::followMultiSegmentPath(graphics &view, path &pathMultiSegment){  
   //TODO: make path creation generic, more than 3 segments must be supported
   view.drawPath(pathMultiSegment.points.at(0), pathMultiSegment.points.at(1), pathMultiSegment.width);
   view.drawPath(pathMultiSegment.points.at(1), pathMultiSegment.points.at(2), pathMultiSegment.width);
   view.drawPath(pathMultiSegment.points.at(2), pathMultiSegment.points.at(3), pathMultiSegment.width);    

   float worldRecord = 1000000;
   point normalPoint;
   point predictedPos;
   pvector distance;
   point start, end;

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
   //view.drawPoint(agent.targetPoint);
   seekTarget();
}