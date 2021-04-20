#include "point.h"

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