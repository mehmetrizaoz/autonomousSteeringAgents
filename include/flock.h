/**
 * @file   flock.h
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  flocking agents scenario
 * @date   15.05.2021
*/

#pragma once

#include "scenario.h"
#include <vector>

using namespace std;

class flock: public scenario{
public:
   /**
   * @brief default constructor.
   */
   flock();

   /**
   * @brief flocking scenario loop function
   * @note opengl callback forces that function to be static
   */
   static void loop();  
};

