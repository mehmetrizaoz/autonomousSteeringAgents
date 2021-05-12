/**
 * @file   path.cpp
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  path class used for path following steering behaviors.
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

}

path::path(float width)
{
   this->width = width;
}

void path::createPath_2()
{
   width = 8;
   this->addPoint(point(-40,  5));
   this->addPoint(point(-14, 15));
   this->addPoint(point( 10,  7));
   this->addPoint(point( 40, 12));
}

void path::createPath_1()
{
   width = 6;
   point start = point(-WIDTH-5,  HEIGHT-40);
   point end   = point( WIDTH+5, -HEIGHT+40);
   this->addPoint(start);
   this->addPoint(end);      
}
