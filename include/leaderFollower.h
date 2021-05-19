/**
 * @file   leaderFollower.h
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  agents follow leader scenario
 * @date   19.05.2021
*/
#pragma once

#include "scenario.h"
#include <vector>

using namespace std;

class leaderFollower: public scenario{
public:
   /**
   * @brief leader velocity
   */
   static pvector leaderVelocity;

   /**
   * @brief leader position
   */
   static point leaderPosition;

   /**
   * @brief default constructor.
   */
   leaderFollower();

   /**
   * @brief leader following scenario loop function
   * @note opengl callback forces that function to be static
   */
   static void loop();  
};

