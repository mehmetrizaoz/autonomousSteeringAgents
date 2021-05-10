#include "obstacle.h"
#include "graphics.h"
#include "point.h"
#include <vector>

using namespace std;

vector<obstacle> obstacle::obstacles;

void obstacle::createObstacle(){
   obstacle obs = obstacle(0, 0, 9);
   
   obstacle::obstacles.push_back(obs);
}

obstacle::obstacle(float x, float y, float r){
   this->x = x;
   this->y = y;
   this->r = r;
}

void obstacle::draw(){
   point p = point(obstacle::obstacles.at(0).x, obstacle::obstacles.at(0).y);
   graphics::drawCircle(p, obstacle::obstacles.at(0).r);
}

