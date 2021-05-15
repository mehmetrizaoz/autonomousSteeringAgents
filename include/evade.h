/**
 * @file   evade.h
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  evade class inherited from scenario class
 * @date   15.05.2021
*/

#pragma once

#include "scenario.h"
#include <vector>

using namespace std;

class evade: public scenario{
public:
   /**
   * Creates scenario
   * @brief default constructor.
   */
   evade();

   /**
   * evading loop function
   * @brief loop function for evading scenario
   * @note opengl callback forces that function to be static
   */
   static void loop();  
};

