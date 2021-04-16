#include "flowField.h"
#include "pvector.h"

flowField::flowField(){
    for (int i = 0; i < WIDTH; i++) {
       for (int j = 0; j < HEIGHT; j++) {
          field[i][j] = pvector(0.1, 0.0);
       }
    }
}

pvector flowField::getField(int x, int y){
   return field[x][y];
}