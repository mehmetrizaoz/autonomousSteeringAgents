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
   * Creates scenario
   * @brief default constructor.
   */
   scenario();   

   /**
   * creates agents
   * @brief agent creation 
   * @param type type of creation method
   * @param count number of agents to be created
   * @param force max force of agents to be created
   * @param speed max speed of agents to be created
   */
   void createAgent(int type, int *count, float *force, float *speed);

   /**
   * graphics initialization
   * @brief initializing of openGL
   * @param argv list of user arguments
   * @param argc number of user arguments
   */  
   void initGL(int * argv, char** argc);   
   
   /**
   * applying force, upodating position etc for all items
   * @brief refresh behavior for all items 
   * @note opengl callback forces that function to be static
   */
   static void refresh();

   /**
   * existing agents stored in that variable
   * @brief all the agents
   * @note opengl callback forces that function to be static
   */
   static vector<agent> agents;

   /**
   * used to apply graphics operations
   * @brief graphics instance
   * @note opengl callback forces that function to be static
   */
   static graphics  view;

   /**
   * used to apply steering behaviors
   * @brief behavior instance
   * @note opengl callback forces that function to be static
   */
   static steeringBehavior behavior;

   /**
   * used to apply color behaviors
   * @brief color instance
   * @note opengl callback forces that function to be static
   */
   static color myColor;   

   /**
   * used to display scenario on screen
   * @brief name of the scenario
   * @note opengl callback forces that function to be static
   */
   static string name;

   /**
   * used as main loop in derived classes
   * @brief openGL screen refresh callback function
   */
   void (*callback)(); 
private:
   void createRandomAgents(int agentCount, float mForce, float mSpeed);      
   void createStaticAgents();
   void createTroop(int agentCount);
};
