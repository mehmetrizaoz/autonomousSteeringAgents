#include "flowField.h"

flowField::flowField(pvector p){
   uniformVectorField(p);
}

flowField::flowField(){}

void flowField::randomField(){
//TODO: implement
}

void flowField::perlinNoise(){
//TODO: implement
}

void flowField::uniformVectorField(pvector p){
   for (int i = 0; i < WIDTH; i++) {
      for (int j = 0; j < HEIGHT; j++) {
         uniformField[i][j] = pvector(p);
      }
   }
}

pvector flowField::getField(int x, int y){
   return uniformField[x][y];
}
/*
void flowField::createRandomArray(int *arr, int size){
   srand(time(NULL));
   for(int i=0; i<size; i++)
      arr[i] = i+1;        

   for (int i=0; i < size; i++){
      int r = rand() % size;
      swap(arr[i], arr[r]);
   }     
}*/