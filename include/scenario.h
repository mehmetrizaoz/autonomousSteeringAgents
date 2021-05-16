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
   * @brief agent creation 
   * @param type type of creation method
   * @param count number of agents to be created
   * @param force max force of agents to be created
   * @param speed max speed of agents to be created
   */
   void createAgent(int type, int *count, float *force, float *speed);

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
   * @brief color instance used
   * @note opengl callback forces that function to be static
   */
   static color myColor;   

   /**
   * @brief scenario name
   * @note opengl callback forces that function to be static
   */
   static string name;

   /**
   * @brief openGL screen refresh callback function, used as main loop in derived classes
   */
   void (*callback)(); 
private:
   void createRandomAgents(int agentCount, float mForce, float mSpeed);      
   void createStaticAgents();
   void createTroop(int agentCount);
};
