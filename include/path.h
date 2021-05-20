/**
 * @file   path.h
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  path class used for path following steering behaviors.
 * @date   12.05.2021
*/

#pragma once

#include "point.h"
#include "entity.h"
#include "color.h"
#include <vector>

using namespace std;

class path : public entity{
public:
   /**
   * @brief default constructor.
   * @see path(float width)
   */
   path();
   
   /**   
   * @brief donstructor.
   * @param width The width of the path.
   * @see path()
   */
   path(float width);

   /**
   * @brief adds a new point to the path
   * @param point to add to the path   
   */
   void addPoint(point p); 

   /**
   * @brief list of points added to the path
   */
   vector<point> points;

   void setPathWidth(int w);
   int getPathWidth();
   /**   
   * @brief overriden draw implementation
   */
   void draw(graphics view);
private:
   /**   
   * @brief width of the path
   */
   int width;

};
