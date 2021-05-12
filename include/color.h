#pragma once

#include <vector>

using namespace std;

enum num{ BLACK=0, BLUE, GREEN, CYAN, RED, MAGENDA, YELLOW, WHITE };

class color{
public:
   color(float r, float g, float b);
   color();
   float R;
   float G;
   float B;
   color getColor(int i);
   vector<color> colors;
   void createColors();
};
