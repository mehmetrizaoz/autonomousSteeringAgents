#include "pvector.h"
#include "math.h"
#include <iostream>

using namespace std;

pvector::pvector(float x, float y){
   this->x = x;
   this->y = y;
}

void pvector::add(pvector *v){
   x = x + v->x;
   y = y + v->y;
}

void pvector::set(float x, float y){
   this->x = x;
   this->y = y;
}

void pvector::sub(pvector *v){
   this->x = this->x - v->x;
   this->y = this->y - v->y;     
}

float pvector::getMagnitude(pvector *v){
   return sqrt((v->x * v->x) + (v->y * v->y));
}

void pvector::normalize(){
   float magnitude = pvector::getMagnitude(this);
   this->x = this->x / magnitude;
   this->y = this->y / magnitude;   
}

void pvector::limit(int limit){
   if(this->x >  limit)
      this->x =  limit;
   if(this->x < -limit)
      this->x = -limit;
   if(this->y >  limit)
      this->y =  limit;
   if(this->y < -limit)
      this->y = -limit;
}