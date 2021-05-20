/**
 * @file   obstacle.cpp
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  obstacle class implementation
 * @date   12.05.2021
*/

#include "obstacle.h"
#include "graphics.h"
#include "point.h"
#include "entity.h"
#include <vector>

using namespace std;

obstacle::obstacle()
{
   p = point(0,0);
   r = 5;
   setColor(RED);
}

obstacle::obstacle(point p, float r)
{
   this->p = p;   
   this->r = r;
   setColor(RED);
}

void obstacle::draw(graphics view){
   view.drawCircle(p, r, getColor());
}

point obstacle::getCenter(){
   return p;
}

void obstacle::setCenter(point p){
   this->p = p;   
}

float obstacle::getRadius(){
   return r;
}

void obstacle::setRadius(float r){
   this->r = r;
}
