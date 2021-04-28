#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include "agent.h"
#include "flowField.h"
#include "graphics.h"
#include <iostream>
#include "color.h"
#include <GL/glut.h> 

class behavior{
   void addCohesionForce(vector<agent> boids, graphics &view);
   

};

#endif