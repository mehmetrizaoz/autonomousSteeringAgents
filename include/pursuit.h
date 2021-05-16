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
   * @brief default constructor.
   */
   pursuit();

   /**   
   * @brief pursuing scenario loop function
   * @note opengl callback forces that function to be static
   */
   static void loop();  
};

