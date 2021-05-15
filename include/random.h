/**
 * @file   random.h
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  utility class for random operations
 * @date   15.05.2021
*/
#pragma once

class random{
public:
   /**
   * random array generation
   * @brief generates random array usin swap between its elements
   * @param arr int array that will include random values
   * @param size size of the array
   */
   static void createRandomArray(int *arr, int size);   
};
