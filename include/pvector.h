#ifndef PVECTOR_H
#define PVECTOR_H

class pvector{
public:
   float x;
   float y;
   pvector();
   pvector(float x, float y);
   float magnitude();   
   void normalize();
   void div(float i);
   void limit(float limit);
   float getAngle();
   float dot(pvector v);
   float angleBetween(pvector v);
   pvector operator + (pvector const &obj);
   pvector operator - (pvector const &obj);
};

#endif
