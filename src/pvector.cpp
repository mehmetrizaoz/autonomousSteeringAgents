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

void pvector::sub(pvector *v){
   x = x - v->x;
   y = y - v->y;     
}

float pvector::magnitude(){
   return sqrt((x * x) + (y *y));
}

