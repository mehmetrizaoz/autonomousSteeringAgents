/**
 * @file   flowField.cpp
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  flowField class implementation
 * @date   13.05.2021
*/

#include "flowField.h"

flowField::flowField(pvector p)
{
   uniformVectorField(p);
}

flowField::flowField(){}

void flowField::randomField()
{
//TODO: implement
}

void flowField::perlinNoise()
{
//TODO: implement
}

void flowField::uniformVectorField(pvector p)
{
   for (int i = 0; i < WIDTH; i++) {
      for (int j = 0; j < HEIGHT; j++) {
         uniformField[i][j] = pvector(p);
      }
   }
}

pvector flowField::getField(int x, int y)
{
   return uniformField[x][y];
}

