#pragma once

#include "point.h"
#include "color.h"
#include "flowField.h"
#include <vector>
#include <string>

using namespace std;

#define WITH_ARRIVING    true
#define WITHOUT_ARRIVING false

class path;

class agent{
public:
  agent(float x, float y);
  ~agent();
  void updatePosition();
  void setMaxSpeed(float s);
  void setR(float s);
  void setMass(float m);
  void setMaxForce(float f);
  void applyForce();
  void setFeatures(float s, float f, float r, float m);
//utility
  void addSteeringForce(float multiplier);
//behaviors  
  void seek(bool arriving);  
  void separation(vector<agent> agents, float multiplier);
  void cohesion(vector<agent> boids, float multiplier);
  void align(vector<agent> boids, float multiplier);  
//private:
  string   name;
  color    vehicleColor;
  point    position;
  pvector  velocity;  
  point    targetPoint;
  float    maxSpeed; 
  float    maxForce;
  pvector  steering;
  pvector  force;
  pvector  acceleration;
  pvector  desiredVelocity;
  float    r;
  float    mass;
};

