/**
 * @file   obstacleAvoidance.h
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  agents avoid from obstacles scenario
 * @date   15.05.2021
*/
#pragma once

#include "scenario.h"
#include "obstacle.h"
#include <vector>

using namespace std;

class obstacleAvoidance: public scenario{
public:
   /**
   * Creates scenario
   * @brief default constructor.
   */
   obstacleAvoidance();

   /**
   * obstacle avoidance loop function
   * @brief loop function for evading scenario
   * @note opengl callback forces that function to be static
   */
   static void loop(); 

   /**
   * @brief list of obstacles
   * @note opengl callback forces that function to be static
   */
   static vector<obstacle> obstacles;

   /**
   * @brief obstacle creation
   * @param obstacles obstacle list to be created
   * @note opengl callback forces that function to be static
   */
   static void createObstacle(vector<obstacle> &obstacles); 
};

