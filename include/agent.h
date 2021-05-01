#pragma once

#include "point.h"
#include "color.h"
#include "flowField.h"
#include <vector>
#include <string>

using namespace std;

#define FOLLOW_MOUSE   1 
#define STAY_IN_FIELD  2
#define IN_FLOW_FIELD  3
#define STAY_IN_PATH   4
#define STAY_IN_PATH_2 5
#define FLOCK          6
#define PURSUIT        7
#define HIDE           8
#define PATH_LOOP      9

#define WITH_ARRIVING    true
#define WITHOUT_ARRIVING false

class path;

//TODO: create steering class using behaviors 
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
  void curvedPath(path &path);
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

