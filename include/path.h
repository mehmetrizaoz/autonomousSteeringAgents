/**
 * @file   path.h
 * @author Mehmet Rıza Öz
 * @brief  path class used for path following steering behaviors.
 * @date   12.05.2021
*/

#pragma once

#include "point.h"
#include <vector>

using namespace std;

class path{
public:
   /**
   * Create a new path object.
   * @brief Default constructor.
   * @see path(float width)
   */
   path();
   
   /**
   * Create a new path object.
   * @brief Constructor.
   * @param width The width of the path.
   * @see path()
   */
   path(float width);

   /**
   * Used when customizing path
   * @brief adds a new point to the path
   * @param point new point to add to the path   
   */
   void addPoint(point p); 

   /**
   * Used when customizing path
   * @todo move this routine to client side
   */   
   void createPath_1();

   /**
   * Used when customizing path
   * @todo move this routine to client side
   */   
   void createPath_2();

   /**
   * path is created from these points
   * @brief points added to the path
   */
   vector<point> points;

   /**
   * path width
   * @brief defines width of the path
   */
   int width; 

};
