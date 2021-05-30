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
   * @brief default constructor.
   */
   obstacleAvoidance();

   /**
   * @brief obstacle avoidance scenario loop function
   * @note opengl callback forces that function to be static
   * @todo: bug: too many obstacle cause disregarding obstacles
   */
   static void loop(); 

   /**
   * @brief list of obstacles
   * @note opengl callback forces that function to be static
   */
   static vector<obstacle> obstacles;

   /**
   * @brief creation of list of obstacles
   * @param obstacles list to be created
   * @note opengl callback forces that function to be static
   */
   static void createObstacle(vector<obstacle> &obstacles); 
};

