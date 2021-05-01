#include "path.h"

void path::addPoint(point p){
   points.push_back(p);
   
}

path::path(){}

path::path(float width){
   this->width = width;
}