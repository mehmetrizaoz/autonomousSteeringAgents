#pragma once

#include "point.h"
#include <vector>

using namespace std;

/**
 * @brief path class used for path following implementations.
*/

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

   void addPoint(point p);
   void createPath_1();
   void createPath_2();
   vector<point> points;
   int width; 

};
