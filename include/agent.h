/**
 * @file   agent.h
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  agent class defines all agent specifications
 * @date   14.05.2021
*/

#pragma once

#include "point.h"
#include "color.h"
#include "entity.h"
#include "flowField.h"
#include <vector>
#include <string>

using namespace std;

class path;

class agent : public entity{
public:
  /**
  * @brief default constructor.
  * @see agent(float x, float y)
  */
  agent();

  /**
  * @brief constructor.
  * @param x position x of the agent 
  * @param y position y of the agent        
  * @see agent()
  */
  agent(float x, float y);

  /**
  * @brief destructor
  */
  ~agent();
    
  /**
  * @brief position update calculations
  * @param arrive has arriving behavior or not
  */    
  void updatePosition(bool arrive);

  /**
  * @brief initialize the agent attributes
  * @param s maximum velocity
  * @param f maximum force
  * @param r radius for arriving behavior
  * @param m mass
  */
  void setFeatures(float s, float f, float r, float m);

  /**
  * @brief name attribute getter
  */
  string getName();

  /**
  * @brief name attribute setter
  * @param n set value
  */
  void setName(string n);

  /**
  * @brief mass attribute getter
  */
  float getMass();

  /**
  * @brief mass attribute setter
  * @param m set value
  */
  void setMass(float m);

  /**
  * @brief agent drawing
  * @param view graphics to draw
  */ 
  void draw(graphics view) override;

  /**
  * @brief velocity attribute getter
  */
  pvector getVelocity();

  /**
  * @brief velocity attribute setter
  * @param v set value
  */
  void setVelocity(pvector v);

  /**
  * @brief target attribute getter
  */
  point getTarget();

  /**
  * @brief target attribute setter
  * @param t set value
  */
  void setTarget(point t);

  /**
  * @brief maximum speed of the agent
  */
  float maxSpeed; 

  /**
  * @brief position of the agent
  */
  point position;

  /**
  * @brief maximum force of the agent
  */
  float maxForce;

  /**
  * @brief steering force of the apply
  */
  pvector steering;

  /**
  * @brief force to apply to the agent
  */
  pvector force;

  /**  
  * @brief acceleration of the agent
  */
  pvector acceleration;

  /**
  * @brief desired velocity of the agent
  */
  pvector desiredVelocity;  

  /**
  * @brief radius for arrive behavior
  */
  float r;
  
  /**  
  * @brief id of the agent
  */
  int id; 

  /**
  * @brief has arriving behavior or not
  */
  bool arrive = false;
  point targetPoint;

private:
  string name;
  float mass;
  pvector velocity;
};

