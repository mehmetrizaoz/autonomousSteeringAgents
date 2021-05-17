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
   entityColor = RED;
}

obstacle::obstacle(point p, float r)
{
   this->p = p;   
   this->r = r;
   entityColor = RED;
}

void obstacle::draw(graphics view){
   view.drawCircle(p, r, entityColor);
}