#include "pvector.h"
#include "math.h"
#include <iostream>

#define PI          3.14159265

using namespace std;

float pvector::angle(){
   float angle;
   angle = atan2 (this->y, this->x) * 180 / PI;
   return angle;
}

pvector::pvector(float x, float y){
   this->x = x;
   this->y = y;
}

void pvector::add(pvector *v){
   x = x + v->x;
   y = y + v->y;
}

void pvector::div(float i){
   x = x / i;
   y = y / i;
}

void pvector::set(float x, float y){
   this->x = x;
   this->y = y;
}

void pvector::sub(pvector *v){
   this->x = this->x - v->x;
   this->y = this->y - v->y;     
}

float pvector::magnitude(){
   return sqrt((this->x * this->x) + (this->y * this->y));
}

void pvector::normalize(){
   float magnitude = this->magnitude();
   this->x = this->x / magnitude;
   this->y = this->y / magnitude;   
}

void pvector::limit(float limit){
   if(this->x >  limit)
      this->x =  limit;
   if(this->x < -limit)
      this->x = -limit;
   if(this->y >  limit)
      this->y =  limit;
   if(this->y < -limit)
      this->y = -limit;
}