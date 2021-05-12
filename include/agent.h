#pragma once

#include "point.h"
#include "color.h"
#include "flowField.h"
#include <vector>
#include <string>

using namespace std;

#define MAX_NUMBER_OF_AGENTS 50

#define WALL        30
#define DISTANCE    2

class path;

class agent{
public:
  agent(float x, float y);
  agent();
  ~agent();
  void updatePosition(int mode, bool arrive);
  void setFeatures(float s, float f, float r, float m);
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
  int      id; 
  bool     arrive = false;
};

