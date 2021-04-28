#include "agent.h"
#include "flowField.h"
#include "graphics.h"
#include <iostream>
#include "behavior.h"
#include "color.h"
#include <GL/glut.h> 

class agent;

void behavior::addCohesionForce(vector<agent> boids, graphics &view){
   float neighborDist = 10;
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
