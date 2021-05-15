/**
 * @file   windy.h
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  windy air scenario
 * @date   15.05.2021
*/
#pragma once

#include "scenario.h"
#include "flowField.h"
#include <vector>

using namespace std;

class windy: public scenario{
public:
   /**
   * Creates scenario
   * @brief default constructor.
   */
   windy();

   /**
   * windy loop function
   * @brief loop function for evading scenario
   * @note opengl callback forces that function to be static
   */
   static void loop();  

   /**
   * @brief flow field instance
   * @note opengl callback forces that function to be static
   */
   static flowField flow;
};

