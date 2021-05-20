/**
 * @file   color.cpp
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  color class implementation
 * @date   13.05.2021
*/

#include "color.h"
#include <vector>

using namespace std;

color::color()
{

}

color::color(float r, float g, float b)
{
    R = r;
    G = g;
    B = b;
}

color color::getColor(int index){    
    switch (index)
    {
       case 0: return WHITE; break;
       case 1: return BLUE; break;
       case 2: return RED; break;
       case 3: return YELLOW; break;
       case 4: return GREEN; break;
       case 5: return BLACK; break;
       case 6: return CYAN; break;
       case 7: return MAGENDA; break;   

    }
    return RED;
}
