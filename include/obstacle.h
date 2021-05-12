/**
 * @file   obstacle.h
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  circular obstacles for agent avoidance behaviors
 * @date   12.05.2021
*/

#pragma once

#include "point.h"

class obstacle{
public:
   /**
   * Create a new obstacle object.
   * @brief Default constructor.
   * @see obstacle(point p, float r);
   */
   obstacle();   

   /**
   * Create a new obstacle object.
   * @brief Constructor 
   * @param p center of the circular obstacle
   * @param r radius of the obstacle
   * @see obstacle(point p, float r);
   */
   obstacle(point p, float r);

   /**
   * center point of the obstacle
   * @brief x and y coordinates
   */
   point p;

   /**
   * radius of the obstacle
   * @brief the bigger radius the bigger the obstacle
   */
   float r;
};
