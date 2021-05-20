/**
 * @file   obstacle.h
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  circular obstacles for agent avoidance behaviors
 * @date   12.05.2021
*/

#pragma once

#include "point.h"
#include "graphics.h"
#include "color.h"
#include "entity.h"

class obstacle : public entity{
public:
   /**
   * @brief default constructor.
   * @see obstacle(point p, float r
   */
   obstacle();   

   /**
   * @brief constructor 
   * @param p center of the circular obstacle
   * @param r radius of the obstacle
   * @see obstacle(point p, float r);
   */
   obstacle(point p, float r);


   point getCenter();
   void setCenter(point p);
   float getRadius();
   void setRadius(float r);

   /**   
   * @brief overriden draw implementation
   */
   void draw(graphics view) override;
   
private:
   /**   
   * @brief center point of the obstacle
   */
   point p;

   /**   
   * @brief radius of the obstacle
   */
   float r;


};
