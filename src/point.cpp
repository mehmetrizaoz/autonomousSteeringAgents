/**
 * @file   point.cpp
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  point class implementation file
 * @date   15.05.2021
*/

#include "point.h"
#include "pvector.h"
#include <string>
#include <iostream>
#include "math.h"

using namespace std;

point::point(float x, float y)
{
   this->x = x;
   this->y = y;
}

point::point()
{
   x = 0;
   y = 0;
}

void point::rotateByAngleAboutPoint(point p, float angle){
   pvector agentTargetToMainTarget = *this - p;
   float diff = p.difference( *this );
   float angleAboutMainTarget = agentTargetToMainTarget.getAngle();
   
   *this = point (diff * cos((angleAboutMainTarget + angle) * PI / 180),
                              diff * sin((angleAboutMainTarget + angle) * PI / 180));
   *this = p + *this;
}

void point::rotate(float angle){
   float currentAngle;
   currentAngle = atan2 (this->y, this->x) * 180 / PI;
   float r = sqrt(this->x * this->x + this->y * this->y);   
   this->x = r * cos((currentAngle + angle) * PI / 180);
   this->y = r * sin((currentAngle + angle) * PI / 180);
}

float point::difference(point &obj){
   return sqrt( (x - obj.x) * (x - obj.x) + (y - obj.y) * (y - obj.y) );
}

point point::operator + (pvector const &obj)
{
   point res;
   res.x = x + obj.x;
   res.y = y + obj.y;
   return res;
}

bool point::operator == (point const &obj)
{
   if(x == obj.x && y == obj.y)
      return true;
   return false;
}

void point::div(float d)
{
   x = x / d;
   y = y / d;
}

void point::mul(float d)
{
   x = x * d;
   y = y * d;
}


point point::operator + (point const &obj)
{
   point res;
   res.x = x + obj.x;
   res.y = y + obj.y;
   return res;
}

pvector point::operator - (point const &obj)
{
   pvector res;
   res.x = x - obj.x;
   res.y = y - obj.y;
   return res;
}

void point::getNormalPoint(point predicted, point start, point end)
{
   pvector a = predicted - start;
   pvector b = end - start;
   b.normalize();
   float a_dot_b = a.dotProduct(b);  
   b.mul(a_dot_b);   
   point normalPoint = start + b;
   this->x = normalPoint.x;
   this->y = normalPoint.y;
}

void point::print(const string &s)
{
   cout << " " << s << " " << x << " " << y << endl;
}
