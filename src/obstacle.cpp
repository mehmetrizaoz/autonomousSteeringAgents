#include "obstacle.h"
#include "graphics.h"
#include "point.h"
#include <vector>

using namespace std;

vector<obstacle> obstacle::obstacles;

void obstacle::createObstacle(){
   obstacle obs = obstacle( point(0,0), 8);
   
   obstacle::obstacles.push_back(obs);
}

obstacle::obstacle(point p, float r){
   this->p = p;   
   this->r = r;
}

void obstacle::draw(){
   point p = obstacle::obstacles.at(0).p;
   graphics::drawCircle(p, obstacle::obstacles.at(0).r);
}

