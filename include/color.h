/**
 * @file   color.h
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  color class used for agent, path, wall etc. color
 * @date   13.05.2021
*/

#pragma once

#include <vector>

using namespace std;

/**
* color names for fundamental colors
* @brief used to get color from colors vector
*/   
enum num{ BLACK=0, BLUE, GREEN, CYAN, RED, MAGENDA, YELLOW, WHITE };

class color{
public:
   /**
   * Create a new color object.
   * @brief default constructor.
   * @see color(float r, float g, float b)
   */
   color();

   /**
   * Create a new color object.
   * @brief Constructor.
   * @param r red (0-255)
   * @param g green (0-255)
   * @param b blue (0-255)
   * @see path()
   */
   color(float r, float g, float b); 

   /**
   * creates main colors for future use
   * @brief fills colors vector with 8 main colors in color bar
   */   
   void createColors();

   /**
   * returns specified color from colors vector
   * @brief Constructor.
   * @param i gets specified color
   * @return requested pre-created color instance
   */
   color getColor(int i);

   /**
   * red color ratio
   * @brief red condiment
   */   
   float R;

   /**
   * green color ratio
   * @brief green condiment
   */   
   float G;

   /**
   * blue color ratio
   * @brief blue condiment
   */   
   float B;

   /**
   * vector of fundamental colors
   * @brief stores main colors
   */   
   vector<color> colors;
};
