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

   /**   
   * @brief getter of the center point attibute
   */
   point getCenter();

   /**   
   * @brief setter of the center point attibute
   */
   void setCenter(point p);

   /**   
   * @brief getter of the radius attibute
   */
   float getRadius();

   /**   
   * @brief setter of the radius attibute
   */
   void setRadius(float r);

   /**   
   * @brief overriden draw implementation
   */
   void draw(graphics view) override;
   
private:
   point p;
   float r;


};
