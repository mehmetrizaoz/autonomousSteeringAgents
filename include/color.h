/**
 * @file   color.h
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  color class used for agent, path, wall etc. color
 * @date   13.05.2021
*/

#pragma once

#define BLACK   color(0,0,0)
#define BLUE    color(0,0,1)
#define GREEN   color(0,1,0)
#define CYAN    color(0,1,1)
#define RED     color(1,0,0)
#define YELLOW  color(1,1,0)
#define MAGENDA color(1,0,1)
#define WHITE   color(1,1,1)

#include <vector>

using namespace std;

class color{
public:
   /**   
   * @brief default constructor.
   * @see color(float r, float g, float b)
   */
   color();  

   /**
   * @brief constructor.
   * @param r red (0-255)
   * @param g green (0-255)
   * @param b blue (0-255)
   * @see path()
   */
   color(float r, float g, float b);

   /**
   * @brief portion of red color
   */   
   float R;
 
   /**
   * @brief portion of green color
   */   
   float G;

   /**
   * @brief portion of blue color
   */   
   float B;

   /**
   * @brief gets colorbar colors
   * @param index color id
   */   
   static color getColor(int index);
};
