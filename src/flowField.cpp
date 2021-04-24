#include "flowField.h"
#include "pvector.h"

flowField::flowField(){
   uniformVectorField();
}

void flowField::randomField(){
//TODO: implement
}

void flowField::perlinNoise(){
//TODO: implement
}

void flowField::uniformVectorField(){
   for (int i = 0; i < WIDTH; i++) {
      for (int j = 0; j < HEIGHT; j++) {
         field[i][j] = pvector(0.005, 0.0);
      }
   }
}

pvector flowField::getField(int x, int y){
   return field[x][y];
}