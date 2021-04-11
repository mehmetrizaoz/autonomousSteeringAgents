#include "pvector.h"

pvector::pvector(float x, float y){
   this->x = x;
   this->y = y;
}

void pvector::add(pvector *v){
   this->x = this->x + v->x;
   this->y = this->y + v->y;   
}

void pvector::sub(pvector *v){
   this->x = this->x - v->x;
   this->y = this->y - v->y;     
}
