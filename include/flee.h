/**
 * @file   flee.h
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  agents flee from mouse scenario
 * @date   15.05.2021
*/
#pragma once

#include "scenario.h"
#include <vector>

using namespace std;

class flee: public scenario{
public:
   /**
   * @brief default constructor.
   */
   flee();

   /**
   * @brief evading scenario loop function
   * @note opengl callback forces that function to be static
   */
   static void loop();  
};

