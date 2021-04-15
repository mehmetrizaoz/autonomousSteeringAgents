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
pvector::pvector(){}

pvector::pvector(float x, float y){
   this->x = x;
   this->y = y;
}

void pvector::div(float i){
   x = x / i;
   y = y / i;
}

void pvector::set(float x, float y){
   this->x = x;
   this->y = y;
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

pvector pvector::operator + (pvector const &obj) {
      pvector res; //TODO: leak ?
      res.x = x + obj.x;
      res.y = y + obj.y;
      return res;
}
pvector pvector::operator - (pvector const &obj) {
      pvector res; //TODO: leak ?
      res.x = x - obj.x;
      res.y = y - obj.y;
      return res;
}