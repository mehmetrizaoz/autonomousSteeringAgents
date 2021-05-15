/**
 * @file   mouseFollower.h
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  agents follow mouse scenario
 * @date   15.05.2021
*/
#pragma once

#include "scenario.h"
#include <vector>

using namespace std;

class mouseFollower: public scenario{
public:
   /**
   * Creates scenario
   * @brief default constructor.
   */
   mouseFollower();

   /**
   * mouse following loop function
   * @brief loop function for evading scenario
   * @note opengl callback forces that function to be static
   */
   static void loop();  
};

