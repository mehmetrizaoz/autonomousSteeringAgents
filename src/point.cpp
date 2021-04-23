#include "point.h"
#include "pvector.h"

point::point(float x, float y){
   this->x = x;
   this->y = y;
}

point::point(){}

point point::operator + (pvector const &obj) {
      point res;
      res.x = x + obj.x;
      res.y = y + obj.y;
      return res;
}

pvector point::operator - (point const &obj) {
      pvector res;
      res.x = x - obj.x;
      res.y = y - obj.y;
      return res;
}

point point::getNormalPoint(point predicted, point start, point end){
   pvector a = predicted - start;
   pvector b = end - start;
   b.normalize();
   float a_dot_b = a.dotProduct(b);  
   b.mul(a_dot_b);   
   point normalPoint = start + b;
   return normalPoint;
}