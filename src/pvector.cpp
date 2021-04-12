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

float pvector::getMagnitude(pvector *v){
   return sqrt((v->x * v->x) + (v->y * v->y));
}

