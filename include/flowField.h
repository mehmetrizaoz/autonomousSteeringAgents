/**
 * @file   flowField.h
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  flowField class, screen can be filled with a force for each pixel
 * @date   13.05.2021
*/

#pragma once

#include "pvector.h"

#define FIELD_WIDTH       34 //TODO: remove these definitions, make themconstructor parameters
#define FIELD_HEIGHT      34

#define WIND_WEST 0.1,  0.0
#define GRAVITY   0.0, -0.1

class flowField{
public:
   /**
   * @brief default constructor.
   * @see flowField(pvector p)
   */
   flowField();

   /**
   * @brief constructor.
   * @param p force vector
   * @see flowField()
   */
   flowField(pvector p);

   /**
   * @brief get force at individual pixel
   * @param x coordinate
   * @param y coordinate
   * @return force at specified position
   */
   pvector getField(int x, int y);

private:   
   void createFlowField(pvector p);
   void perlinNoise();
   void randomField();
   pvector uniformField[FIELD_WIDTH][FIELD_HEIGHT];
};
