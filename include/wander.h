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
   * @brief default constructor
   * @todo business logic will be changed
   */
   wander();

   /**
   * @brief wander scenario loop function
   * @note opengl callback forces that function to be static
   */
   static void loop();  
};

