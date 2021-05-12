#include "color.h"
#include <vector>

using namespace std;

color::color(float r, float g, float b){
    R = r;
    G = g;
    B = b;
}

color color::getColor(int i){
    return colors.at(i);
}

color::color(){}

void color::createColors(){ //TODO: move to colors
   colors.push_back(color(0.0, 0.0, 0.0));
   colors.push_back(color(0.0, 0.0, 1.0));
   colors.push_back(color(0.0, 1.0, 0.0));
   colors.push_back(color(0.0, 1.0, 1.0));
   colors.push_back(color(1.0, 0.0, 0.0));
   colors.push_back(color(1.0, 0.0, 1.0));
   colors.push_back(color(1.0, 1.0, 0.0));
   colors.push_back(color(1.0, 1.0, 1.0));
}

