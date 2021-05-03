#include "random.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

void random::createRandomArray(int *arr, int size){
   srand(time(NULL));
   for(int i=0; i<size; i++)
      arr[i] = i+1;        

   for (int i=0; i < size; i++){
      int r = rand() % size;
      swap(arr[i], arr[r]);
   }     
}