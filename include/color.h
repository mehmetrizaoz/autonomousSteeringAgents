#pragma once

#include <vector>

using namespace std;

class color{
public:
   color(float r, float g, float b);
   color();
   float R;
   float G;
   float B;
   static vector<color> colors; //move to client code
   static void createColors();
};
