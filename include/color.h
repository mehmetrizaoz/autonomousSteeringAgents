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
   static vector<color> colors; //TODO: move tocli,ent code
   static void createColors();
};
