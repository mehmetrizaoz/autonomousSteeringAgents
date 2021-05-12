/**
 * @file   obstacle.h
 * @author Mehmet Rıza Öz
 * @brief  circular obstacles for agent avoidance behaviors
 * @date   12.05.2021
*/

#pragma once

#include "point.h"

class obstacle{
public:
   obstacle();      
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
