#pragma once

#include <string>

#define PI          3.14159265

using namespace std;

class point;

class pvector{
public:
   float x;
   float y;
   pvector();
   pvector(float x, float y);
   float magnitude();   
   pvector & normalize();
   void  div(float i);
   void  mul(float i);
   void  add(pvector p);
   void  limit(float limit);
   float getAngle();
   float dotProduct(pvector v);
   float angleBetween(pvector v);
   pvector operator += (pvector const &obj);   
   pvector operator +  (pvector const &obj);
   pvector operator -  (pvector const &obj);
   bool    operator == (pvector const &obj);
   pvector operator -  (point const &obj);
   pvector operator +  (point const &obj);
   void print(const string &s);
};
