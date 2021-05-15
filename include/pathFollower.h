/**
 * @file   pathFollower.h
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  path following scenario
 * @date   15.05.2021
*/
#pragma once

#include "scenario.h"
#include <vector>

using namespace std;

class pathFollower: public scenario{
public:
   /**
   * Creates scenario
   * @brief default constructor.
   */
   pathFollower();

   /**
   * path follower avoidance loop function
   * @brief loop function for evading scenario
   * @note opengl callback forces that function to be static
   */
   static void loop();  

   /**
   * path creating
   * @brief creates path
   * @param path to create
   * @note opengl callback forces that function to be static
   */
   static void createPath(path &p);

   /**
   * path instance
   * @brief used to access path class behaviors
   * @note opengl callback forces that function to be static
   */
   static path myPath;
};

