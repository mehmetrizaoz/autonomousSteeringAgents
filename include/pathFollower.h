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
   * @brief default constructor.
   */
   pathFollower();

   /**   
   * @brief path follower scenario loop function
   * @note opengl callback forces that function to be static
   */
   static void loop();  

   /**
   * @brief creates path
   * @param path to create
   * @note opengl callback forces that function to be static
   */
   static void createPath(path &p);

   /**
   * @brief path that will be followed
   * @note opengl callback forces that function to be static
   */
   static path myPath;
};

