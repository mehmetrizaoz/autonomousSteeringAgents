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
   * @brief random array generation
   * @param arr struct that includes random values
   * @param size of the array
   */
   static void createRandomArray(int *arr, int size);   
};
