/**
 * @file   path.cpp
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  path class implementation
 * @date   12.05.2021
*/

#include "path.h"
#include "graphics.h"

void path::addPoint(point p)
{
   points.push_back(p);   
}

path::path()
{
   setColor(BLUE);
   width = 8;
}

path::path(float width)
{
   this->width = width;
   setColor(BLUE);
}

void path::draw(graphics view){
  view.drawPath(*this);
}