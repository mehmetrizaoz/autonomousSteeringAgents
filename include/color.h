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
* @brief fundament list of al colors
*/   
enum num{ BLACK=0, BLUE, GREEN, CYAN, RED, MAGENDA, YELLOW, WHITE };

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
   * @brief creation of fundamental 8 colors
   */   
   void createColors();

   /**
   * @brief gets requested color
   * @param i color index
   * @return requested color
   */
   color getColor(int index);

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
   * @brief storage structure of created fundamental colors
   */   
   vector<color> colors;
};
