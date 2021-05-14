/**
 * @file   agent.h
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  agent class defines all agent specifications
 * @date   14.05.2021
*/

#pragma once

#include "point.h"
#include "color.h"
#include "flowField.h"
#include <vector>
#include <string>

using namespace std;

class path;

class agent{
public:
  /**
  * Creates new agent object.
  * @brief default constructor.
  * @see agent(float x, float y)
  */
  agent();

  /**
  * Creates new agent object.
  * @brief Constructor.
  * @param x position x of the agent 
  * @param x position y of the agent        
  * @see agent()
  */
  agent(float x, float y);

  /**
  * invokes when instance is killed
  * @brief agent destructor
  */
  ~agent();
    
  /**
  * position update is invoked in periodically in a loop
  * @brief calculates next position in each update using force applied
  * @param arrive agent has arriving behavior or not
  * @see agent()
  */    
  void updatePosition(bool arrive);

  /**
  * setting parameters
  * @brief used to initialize the agent
  * @param s maximum velocity
  * @param f maximum force
  * @param r radius for arriving behavior
  * @param m mass
  */
  void setFeatures(float s, float f, float r, float m);

  /**
  * used to distinguish specific agent
  * @brief name of the agent
  */
  string   name;

  /**
  * color information passed to graphics
  * @brief color of the agent
  */
  color    fillColor;

  /**
  * position information 
  * @brief x and y coordinates of the agent
  */
  point    position;

  /**
  * velocity vector
  * @brief velocity of the agent
  */
  pvector  velocity;  

  /**
  * calculated target point of the agent
  * @brief target of the agent
  */
  point    targetPoint;

  /**
  * if velocity of the agent is more than this value, limit function restricts velocity
  * @brief maximum speed of the agent
  */
  float    maxSpeed; 

  /**
  * if force of the agent is more than this value, limit function restricts force
  * @brief maximum force of the agent
  */
  float    maxForce;

  /**
  * steering force to change direction
  * @brief steering force to apply
  */
  pvector  steering;

  /**
  * force to apply to agent instance
  * @brief total force to apply
  */
  pvector  force;

  /**
  * acceleration to apply
  * @brief added to velocity in each update
  */
  pvector  acceleration;

  /**
  * desired velocity to reach the target point
  * @brief get using target point and used to get steering force
  */
  pvector  desiredVelocity;  

  /**
  * radius for arrivin behavior
  * @brief agent slows down as target point gets smaller than radius
  */
  float    r;
  
  /**
  * mass of the agent
  * @brief used to get acceleration from force
  */
  float    mass;

  /**
  * identification number of the agent
  * @brief used to distinguish specific agent
  */
  int      id; 

  /**
  * arriving behavior
  * @brief defines if agent will have arriving behavior
  */
  bool     arrive = false;
};

