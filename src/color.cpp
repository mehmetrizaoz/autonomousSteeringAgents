/**
 * @file   color.cpp
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  color class implementation
 * @date   13.05.2021
*/

#include "color.h"
#include <vector>

using namespace std;

color::color(float r, float g, float b)
{
    R = r;
    G = g;
    B = b;
}

color color::getColor(int index)
{
   return colors.at(index);
}

color::color()
{
    
}

void color::createColors()
{
   colors.push_back(color(0.0, 0.0, 0.0));
   colors.push_back(color(0.0, 0.0, 1.0));
   colors.push_back(color(0.0, 1.0, 0.0));
   colors.push_back(color(0.0, 1.0, 1.0));
   colors.push_back(color(1.0, 0.0, 0.0));
   colors.push_back(color(1.0, 0.0, 1.0));
   colors.push_back(color(1.0, 1.0, 0.0));
   colors.push_back(color(1.0, 1.0, 1.0));
}

