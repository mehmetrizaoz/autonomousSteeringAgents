/**
 * @file   wander.h
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  random wandering agents scenario
 * @date   15.05.2021
*/
#pragma once

#include "scenario.h"
#include <vector>

using namespace std;

class wander: public scenario{
public:
   /**
   * Creates scenario
   * @brief default constructor.
   */
   wander();

   /**
   * wandering loop function
   * @brief loop function for evading scenario
   * @note opengl callback forces that function to be static
   */
   static void loop();  
};

