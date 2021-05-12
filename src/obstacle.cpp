/**
 * @file   obstacle.h
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  circular obstacles for agent avoidance behaviors
 * @date   12.05.2021
*/

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

