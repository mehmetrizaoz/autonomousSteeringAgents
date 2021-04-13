#ifndef PVECTOR_H
#define PVECTOR_H

class pvector{
public:
   float x;
   float y;
   pvector(float x, float y);
   static float getMagnitude(pvector *v);   
   void normalize();
   void set(float x, float y);
   void add(pvector *v);
   void sub(pvector *v);
   void limit(int limit);
   
};

#endif
