#include "obstacle.h"
#include "graphics.h"
#include "point.h"
#include <vector>

using namespace std;

obstacle::obstacle(){}

obstacle::obstacle(point p, float r){
   this->p = p;   
   this->r = r;
}

