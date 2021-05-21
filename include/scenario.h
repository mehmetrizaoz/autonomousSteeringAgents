/**
 * @file   scenario.h
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  base class for all scenarios
 * @date   15.05.2021
*/

#pragma once

#include "agent.h"
#include "graphics.h"
#include "steeringBehavior.h"
#include <vector>

using namespace std;

enum types{ RANDOM=0, STATIC, TROOP };

class scenario{
public:
   /**
   * @brief default constructor.
   */
   scenario();   

   /**
   * @brief graphics initialization
   * @param argv list of user arguments
   * @param argc number of user arguments
   */  
   void initGL(int * argv, char** argc);   
   
   /**
   * @brief refreshes all items 
   * @note opengl callback forces that function to be static
   */
   static void refresh();

   /**
   * @brief structure stores agents
   * @note opengl callback forces that function to be static
   */
   static vector<agent> agents;

   /**
   * @brief graphics instance used
   * @note opengl callback forces that function to be static
   */
   static graphics  view;

   /**
   * @brief behavior instance used
   * @note opengl callback forces that function to be static
   */
   static steeringBehavior behavior;

   /**
   * @brief scenario name
   * @note opengl callback forces that function to be static
   */
   static string name;

   /**
   * @brief openGL screen refresh callback function, used as main loop in derived classes
   */
   void (*callback)(); 

   /**
   * @brief random agent creation
   * @param agentCount number of agents
   * @param mForce maxForce 
   * @param mSpeed maxSpeed
   */
   void createRandomAgents(int agentCount, float mForce, float mSpeed);      

   /**
   * @brief static agent creation
   * @param s1 name of the first agent
   * @param s2 name of the second agent
   */
   void createStaticAgents(string s1, string s2);

   /**
   * @brief troop creation
   * @param number of agents in the troop
   */
   void createTroop(int agentCount);
};

