/**
 * @file   pursuit.h
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  one agent pursue other one scenario
 * @date   15.05.2021
*/
#pragma once

#include "scenario.h"
#include <vector>

using namespace std;

class pursuit: public scenario{
public:
   /**
   * Creates scenario
   * @brief default constructor.
   */
   pursuit();

   /**
   * pursuing loop function
   * @brief loop function for evading scenario
   * @note opengl callback forces that function to be static
   */
   static void loop();  
};

