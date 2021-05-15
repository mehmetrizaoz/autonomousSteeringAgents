/**
 * @file   point.h
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  point class used for point operations
 * @date   15.05.2021
*/

#pragma once

#include "pvector.h"
#include <string>

using namespace std;

class point{
public:
   /**
   * create a new point instance
   * @brief default constructor
   * @see point(float x, float y)
   */
   point();

   /**
   * create a new point instance
   * @brief constructor
   * @param x position x of the point
   * @param y position y of the point
   * @see point()
   */
   point(float x, float y); 
   
   /**
   * helper function to divide point position
   * @brief divide point
   * @param d scalar to divide position of the point   
   */
   void div(float d);

   /**
   * helper function to multiply point position
   * @brief multiply point
   * @param d scalar to multiply position of the point   
   */
   void mul(float d);
   
   /**
   * prints position of the point
   * @brief debug function 
   * @param s explanation string of the log
   */  
   void print(const string &s);

   /**
   * provides normal point on a vector of a point
   * @brief gets a points normal point on a vector
   * @param predicted point that caller require normal on the vector
   * @param start start point of the vector
   * @param end end point of the vector
   */
   void getNormalPoint(point predicted, point start, point end);

   /**
   * overloaded + oeprator 
   * @brief used between vector and point
   * @param obj vector to add
   s* @return substracted result
   */  
   point operator + (pvector const &obj);

   /**
   * overloaded + oeprator 
   * @brief used between point and point
   * @param obj point to add
   * @return substracted result
   */  
   point operator + (point const &obj);   

   /**
   * overloaded - oeprator 
   * @brief used between point and point
   * @param obj point to substract
   * @return substracted result
   */  
   pvector operator - (point const &obj);

   /**
   * overloaded == oeprator 
   * @brief used between point and point
   * @param obj point to compare
   */  
   bool operator == (point const &obj);

   /**
   * x coordinate
   * @brief x position of the point   
   */  
   float x;

   /**
   * y coordinate
   * @brief y position of the point   
   */  
   float y;   
};
