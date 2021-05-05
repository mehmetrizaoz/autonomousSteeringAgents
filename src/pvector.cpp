#include "pvector.h"
#include "math.h"
#include "point.h"
#include <iostream>
#include <string>

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

void pvector::mul(float i){
   x = x * i;
   y = y * i;
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
   this->magnitude();
   this->mul(limit);
}

pvector pvector::operator + (pvector const &obj) {
   pvector res;
   res.x = x + obj.x;
   res.y = y + obj.y;
   return res;
}

bool pvector::operator == (pvector const &obj) {      
   if(x == obj.x && y == obj.y)
      return true;
   return false;
}

pvector pvector::operator + (point const &obj){
   pvector res;
   res.x = x + obj.x;
   res.y = y + obj.y;
   return res;
}

pvector pvector::operator - (point const &obj){
   pvector res;
   res.x = x - obj.x;
   res.y = y - obj.y;
   return res;
}

void pvector::print(const string &s){
   cout << s << " " << x << " " << y << endl;
}

pvector pvector::operator - (pvector const &obj) {
   pvector res;
   res.x = x - obj.x;
   res.y = y - obj.y;
   return res;
}
