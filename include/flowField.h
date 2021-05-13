/**
 * @file   flowField.h
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  flowField class, screen can be filled with a force for each pixel
 * @date   13.05.2021
*/

#pragma once

#include "pvector.h"

#define WIDTH       34 //TODO: remove these definitions, make themconstructor parameters
#define HEIGHT      34

#define WIND_WEST 0.1,  0.0
#define GRAVITY   0.0, -0.1

class flowField{
public:
   /**
   * Create a new flowField object.
   * @brief default constructor.
   * @see flowField(pvector p)
   */
   flowField();

   /**
   * Create a new flowField object.
   * @brief constructor.
   * @param p force vector
   * @see flowField()
   */
   flowField(pvector p);

   /**
   * get force for a specific position
   * @brief get force for individual pixel
   * @param x x cprovidesoordinate
   * @param y y coordinate
   * @return returns force at specified position
   */
   pvector getField(int x, int y);

private:   
   void createFlowField(pvector p);
   void perlinNoise();
   void randomField();
   pvector uniformField[WIDTH][HEIGHT];
};
