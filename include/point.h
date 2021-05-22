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
   * @brief default constructor
   * @see point(float x, float y)
   */
   point();

   /**
   * @brief constructor
   * @param x position x of the point
   * @param y position y of the point
   * @see point()
   */
   point(float x, float y); 
   
   /**
   * @brief divide point
   * @param d scalar to divide position of the point   
   */
   void div(float d);

   /**
   * @brief multiply point
   * @param d scalar to multiply position of the point   
   */
   void mul(float d);
   
   /**
   * @brief debug function 
   * @param s explanation string of the log
   */  
   void print(const string &s);

   /**   
   * @brief provides normal point on a vector of a point
   * @param predicted point that caller require normal on the vector
   * @param start point of the vector
   * @param end point of the vector
   */
   void getNormalPoint(point predicted, point start, point end);

   /**   
   * @brief overloaded + operator 
   * @param obj vector to add
   * @return sum
   */  
   point operator + (pvector const &obj);

   /**   
   * @brief overloaded + operator 
   * @param obj point to add
   * @return sum
   */  
   point operator + (point const &obj);   

   /**   
   * @brief overloaded - operator
   * @param obj point to substract
   * @return difference
   */  
   pvector operator - (point const &obj);

   /**   
   * @brief overloaded == operator 
   * @param obj point to compare
   * @return comparison result
   */  
   bool operator == (point const &obj);


   void rotate(float angle);

   /**
   * @brief x position
   */  
   float x;

   /**
   * @brief y position
   */  
   float y;   
};
