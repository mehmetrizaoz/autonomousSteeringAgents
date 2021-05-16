/**
 * @file   steeringBehavior.h
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  functions for autonomous steering behaviors
 * @date   15.05.2021
*/

#pragma once

#include "flowField.h"
#include <vector>
#include "graphics.h"
#include "obstacle.h"

#define CIRCLE_DISTANCE 0.1  //for wandering agents
#define CIRCLE_RADIUS   0.4

#define FOLLOW_MOUSE   1 
#define STAY_IN_FIELD  2
#define IN_FLOW_FIELD  3
#define AVOID_OBSTACLE 4
#define STAY_IN_PATH   5
#define FLOCK          6
#define WANDER         7
#define FLEE           8
#define PURSUIT        9
#define EVADE          10

using namespace  std;

class agent;
class path;
class graphics;

class steeringBehavior{
public:   
   /**
   * @brief gets reflection force
   * @param agent unit to check
   * @param turnpoint defines border to apply force
   * @return force to be applied
   */
   pvector stayInArea(agent &agent, int turnPoint);

   /**
   * @brief gets flow field force
   * @param agent unit to apply flow field
   * @param flow field
   * @return force to be applied
   */
   pvector inFlowField(agent &agent, flowField &flow);

   /**
   * @brief gets force to follow path
   * @param agent to follow the pathk
   * @param path to follow
   * @param view used for debugging
   * @return force to be applied
   */
   pvector stayInPath(agent &agent, path &path, graphics view);

   /**   
   * @brief force to seek
   * @param agent that will go to specific target point
   * @return force to be applied
   */
   pvector seek(agent &agent);

   /**
   * @brief force to separate 
   * @param agent agent that will be stayed away
   * @param agents list of all the agents
   * @return force to be applied
   */
   pvector separation(vector<agent> agents, agent &agent);

   /**   
   * @brief force to cohesion
   * @param agent to go to center of other agents, with specified distance
   * @param boids list of all the agents
   * @return force to be applied
   */
   pvector cohesion(vector<agent> boids, agent &agent);

   /**
   * @brief force to align
   * @param agent to be aligned
   * @param boids list of all the agents
   * @return force to be applied
   */
   pvector align(vector<agent> boids, agent &agent);   

   /**
   * @brief force to wander
   * @param agent agent that will wander
   * @return force to be applied
   */
   pvector wander(agent &agent);   

   /**   
   * @brief force to pursue
   * @param pursuer agent that will follow specified agent
   * @param view used for debugging 
   * @param boids list of all the agents
   * @return force to be applied
   */
   pvector pursuit(vector<agent> boids, agent &pursuer, graphics view, string name);

   /**
   * @brief force to evade
   * @param evader agent that will escape
   * @param view used for debugging 
   * @param boids list of all the agents
   * @return force to be applied
   */
   pvector evade(vector<agent> boids, agent &evader, graphics view, string name);

   /**   
   * @brief force to flee
   * @param agent agent that will flee
   * @param view used for debugging 
   * @param p point that agent flees
   * @return force to be applied
   */
   pvector flee(agent &agent, graphics &view, point p);   

   /**
   * @brief force to avoid
   * @param agent agent that will avoid from obstacles
   * @param obstacles list of all existing objects   
   * @return force to be applied
   */
   pvector avoid(vector<obstacle> obstacles, agent &agent);

   /**
   * @brief applies angle on vector
   * @param angle that will be set
   * @param p vector that angle will be applied
   */
   void setAngle(pvector &p, float angle);
};