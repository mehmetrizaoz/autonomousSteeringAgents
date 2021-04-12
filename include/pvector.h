#ifndef PVECTOR_H
#define PVECTOR_H

class pvector{
public:
   float x;
   float y;
   pvector(float x, float y);
   static float getMagnitude(pvector *v);
   void add(pvector *v);
   void sub(pvector *v);
   
};

#endif
