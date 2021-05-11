#include "obstacle.h"
#include "graphics.h"
#include "point.h"
#include <vector>

using namespace std;

vector<obstacle> obstacle::obstacles;

obstacle::obstacle(){}

void obstacle::createObstacle(){   
   obstacle::obstacles.push_back(obstacle(point(0,0), 8));   
   obstacle::obstacles.push_back(obstacle(point(20,-10), 4));
}

obstacle::obstacle(point p, float r){
   this->p = p;   
   this->r = r;
}

void obstacle::draw(){      
   point p;   
   for(auto it = obstacle::obstacles.begin(); it < obstacle::obstacles.end(); it++){
      p = (*it).p;
      graphics::drawCircle(p, (*it).r);
   }
}

