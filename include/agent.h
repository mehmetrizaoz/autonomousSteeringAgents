#ifndef AGENT_H
#define AGENT_H

#include "pvector.h"
#include "point.h"
#include "color.h"
#include "flowField.h"
#include <vector>
#include <string>

using namespace std;

#define SEEK           1 
#define REFLECT        2
#define FLOW_FIELD     3
#define PATH_SIMPLE    4
#define PATH_COMPLEX   5
#define FLOCK          6
#define FOLLOW_LEAD    7
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
  void addSteeringForce(float multiplier);
  void uniformFlow(flowField &flow);
  void reflect(int wall, int distance);  
  void seek(bool arriving);  
  void separation(vector<agent> agents, float multiplier);
  void cohesion(vector<agent> boids, float multiplier);
  void align(vector<agent> boids, float multiplier);  
  void simplePath(path &path);
  void curvedPath(path &path);
//TODO: make variables private
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

#endif