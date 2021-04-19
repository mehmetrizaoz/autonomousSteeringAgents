#include "pvector.h"
#include "math.h"
#include <iostream>

#define PI          3.14159265

using namespace std;

float pvector::getAngle(){
   float angle;
   angle = atan2 (this->y, this->x) * 180 / PI;
   return angle;
}

float pvector::angleBetween(pvector v){
   float angle = this->dotProduct(v) / (this->magnitude() * v.magnitude());
   angle = acos(angle)  * 180 / PI;
   return angle;
}

//TODO: implement with operator overloading
float pvector::dotProduct(pvector v){
   return ((x * v.x) + (y * v.y));
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
      pvector res;
      res.x = x + obj.x;
      res.y = y + obj.y;
      return res;
}
pvector pvector::operator - (pvector const &obj) {
      pvector res;
      res.x = x - obj.x;
      res.y = y - obj.y;
      return res;
}
