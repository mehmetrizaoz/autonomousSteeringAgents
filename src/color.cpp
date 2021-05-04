#include "color.h"
#include <vector>

using namespace std;

color::color(float r, float g, float b){
    R = r;
    G = g;
    B = b;
}

color::color(){}

vector<color> color::colors;

void color::createColors(){ //TODO: move to colors
   color::colors.push_back(color(0.0, 0.0, 0.0));
   color::colors.push_back(color(0.0, 0.0, 1.0));
   color::colors.push_back(color(0.0, 1.0, 0.0));
   color::colors.push_back(color(0.0, 1.0, 1.0));
   color::colors.push_back(color(1.0, 0.0, 0.0));
   color::colors.push_back(color(1.0, 0.0, 1.0));
   color::colors.push_back(color(1.0, 1.0, 0.0));
   color::colors.push_back(color(1.0, 1.0, 1.0));
}

