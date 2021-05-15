/**
 * @file   pvector.h
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  pvector class used for 2D vector operations
 * @date   15.05.2021
*/
#pragma once

#include <string>

#define PI 3.14159265

using namespace std;

class point;

class pvector{
public:
   /**
   * create a new pvector instance
   * @brief default constructor
   * @see pvector(float x, float y)
   */
   pvector();

   /**
   * create a new pvector instance
   * @brief constructor
   * @param x x magnitude of the vector
   * @param y y magnitude of the vector
   * @see pvector()
   */
   pvector(float x, float y);

   /**
   * uses pisagor theorem for magnitude calculation
   * @brief calculates magnitude of the vector
   * @return magnitude of the vector
   */
   float magnitude();

   /**
   * divides vector by magnitude
   * @brief normalize vector
   * @return normalized vector
   */
   pvector & normalize();
   
   /**
   * vector division
   * @brief divides vector by given scalar value
   * @param i scalar value to divide
   */
   void  div(float i);

   /**
   * vector multiplication
   * @brief multiplies vector by given scalar value
   * @param i scalar value to multiply
   */
   void  mul(float i);

   /**
   * vector addition
   * @brief addition of vectors
   * @param p vector to add
   */
   void  add(pvector p);

   /**
   * vector limitation
   * @brief limits vector with the given parameter
   * @param limit upper limit to restrict vector
   */
   void limit(float limit);

   /**
   * calculates vector angle
   * @brief get angle using its x and y magnitudes
   * @return angle of the vector
   */
   float getAngle();

   /**
   * dot product calculation
   * @brief dot product of two vectors
   * @param v vector to calculate dot product
   * @return returns scalar dot product value
   */
   float dotProduct(pvector v);

   /**
   * angle calculation between two vectors
   * @brief angle is calculated using dot product
   * @param v vector to calculate angle
   * @return angle value between two vectors
   */
   float angleBetween(pvector v);

   /**
   * prints position of the vector
   * @brief debug function 
   * @param s explanation string of the log
   */  
   void print(const string &s);

   /**
   * overloaded += operator 
   * @brief used between vectors
   * @param obj vector to add
   * @return sum of vectors
   */  
   pvector operator += (pvector const &obj);   

   /**
   * overloaded + operator 
   * @brief used between vectors
   * @param obj vector to add
   * @return sum of vectors
   */  
   pvector operator +  (pvector const &obj);

   /**
   * overloaded - operator 
   * @brief used between vectors
   * @param obj vector to substract
   * @return difference of vectors
   */  
   pvector operator -  (pvector const &obj);

   /**
   * overloaded - operator 
   * @brief used between vector and point
   * @param obj point to substract
   * @return difference 
   */  
   pvector operator -  (point const &obj);

   /**
   * overloaded + operator 
   * @brief used between vector and point
   * @param obj point to add
   * @return sum 
   */  
   pvector operator +  (point const &obj);

   /**
   * overloaded == operator 
   * @brief used between vectors
   * @param obj vector to check if equal
   * @return true or false 
   */  
   bool    operator == (pvector const &obj);   

   /**
   * x magnitude of the vector
   * @brief used between vector and point
   */  
   float x;

   /**
   * y magnitude of the vector
   * @brief used between vector and point
   */  
   float y;
};
