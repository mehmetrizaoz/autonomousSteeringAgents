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
   * reflection behavior 
   * @brief returns force to apply if it is near the specified border
   * @param agent unit to check
   * @param turnpoint defines border to apply force
   * @return force to be applied
   */
   pvector stayInArea(agent &agent, int turnPoint);

   /**
   * flow field behavior 
   * @brief applies flow field at agents position
   * @param agent unit to apply flow field
   * @param flow flow field
   * @return force to be applied
   */
   pvector inFlowField(agent &agent, flowField &flow);

   /**
   * multi segment path following behavior
   * @brief agent follows given path
   * @param agent agent to follow the pathk
   * @param path path to follow
   * @param view used for debugging
   * @return force to be applied
   */
   pvector stayInPath(agent &agent, path &path, graphics view);

   /**
   * seek behavior
   * @brief agent goes to specified point
   * @param agent agent that will go to specific target point
   * @return force to be applied
   */
   pvector seek(agent &agent);

   /**
   * separation behavior
   * @brief agent stays away from other agents, with specified distance
   * @param agent agent to be stayed away
   * @param agents list of all the agents
   * @return force to be applied
   */
   pvector separation(vector<agent> agents, agent &agent);

   /**
   * cohesion behavior
   * @brief agent goes at the center of other agents positions
   * @param agent agent to go to center of other agents, with specified distance
   * @param boids list of all the agents
   * @return force to be applied
   */
   pvector cohesion(vector<agent> boids, agent &agent);

   /**
   * align behavior
   * @brief agent velocity aligned with other agents, with specified distance
   * @param agent agent to be aligned
   * @param boids list of all the agents
   * @return force to be applied
   */
   pvector align(vector<agent> boids, agent &agent);   

   /**
   * wandering behavior
   * @brief agent that will wander
   * @param agent agent to be stayed away
   * @return force to be applied
   */
   pvector wander(agent &agent);   

   /**
   * pursuing behavior
   * @brief agent pursuits other agent in all agents
   * @param pursuer agent that will follow specified agent
   * @param view used for debugging 
   * @param boids list of all the agents
   * @return force to be applied
   */
   pvector pursuit(vector<agent> boids, agent &pursuer, graphics view);

   /**
   * evading behavior
   * @brief agent escapes other agent in all agents
   * @param evader agent that will escape
   * @param view used for debugging 
   * @param boids list of all the agents
   * @return force to be applied
   */
   pvector evade(vector<agent> boids, agent &evader, graphics view);

   /**
   * fleeing behavior
   * @brief agent flees from mouse
   * @param agent agent that will flee
   * @param view used for debugging 
   * @param p point that agent flees
   * @return force to be applied
   */
   pvector flee(agent &agent, graphics &view, point p);   

   /**
   * avoidin behavior
   * @brief agent escapes other agent in all agents
   * @param agent agent that will avoid from obstacles
   * @param obstacles list of all existing objects   
   * @return force to be applied
   */
   pvector avoid(vector<obstacle> obstacles, agent &agent);

   /**
   * rotates vector with angle
   * @brief applies angle on vector
   * @param angle angle that will be set
   * @param p vector that angle will be applied
   */
   void setAngle(pvector &p, float angle);
};