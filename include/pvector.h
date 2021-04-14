#ifndef PVECTOR_H
#define PVECTOR_H

class pvector{
public:
   float x;
   float y;
   pvector(float x, float y);
   float magnitude();   
   void normalize();
   void set(float x, float y);
   void add(pvector *v);
   void div(float i);
   void sub(pvector *v);
   void limit(float limit);
   float angle();
};

#endif
