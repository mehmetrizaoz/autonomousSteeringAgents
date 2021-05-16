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
   * @brief default constructor.
   */
   windy();

   /**
   * @brief windy scenario loop function
   * @note opengl callback forces that function to be static
   */
   static void loop();  

   /**
   * @brief flow field used
   * @note opengl callback forces that function to be static
   */
   static flowField flow;
};

