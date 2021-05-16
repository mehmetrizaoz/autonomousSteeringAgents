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
   * @brief default constructor.
   */
   mouseFollower();

   /**
   * @brief mouse following scenario loop function
   * @note opengl callback forces that function to be static
   */
   static void loop();  
};

