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
   * @brief default constructor
   * @see pvector(float x, float y)
   */
   pvector();

   /**
   * @brief constructor
   * @param x magnitude of the vector
   * @param y magnitude of the vector
   * @see pvector()
   */
   pvector(float x, float y);

   /**
   * @brief calculates magnitude of the vector
   * @return magnitude of the vector
   */
   float magnitude();

   /**
   * @brief normalize 
   * @return normalized vector
   */
   pvector & normalize();
   
   /**   
   * @brief vector division
   * @param i scalar value to divide
   */
   void  div(float i);

   /**   
   * @brief vector multiplication
   * @param i scalar value to multiply
   */
   void  mul(float i);

   /**   
   * @brief addition of vectors
   * @param p vector to add
   */
   void  add(pvector p);

   /**
   * @brief vector limitation
   * @param limit value to restrict vector magnitude
   */
   void limit(float limit);

   /**   
   * @brief calculates vector angle
   * @return angle
   */
   float getAngle();

   /**
   * @brief dot product of two vectors
   * @param v vector to calculate dot product
   * @return returns scalar dot product
   */
   float dotProduct(pvector v);

   /**
   * @brief angle calculation between two vectors
   * @param v vector to calculate angle
   * @return angle
   */
   float angleBetween(pvector v);

   /**
   * @brief debug function 
   * @param s identification text
   */  
   void print(const string &s);

   /**
   * @brief overloaded += operator
   * @param obj vector to add
   * @return sum
   */  
   pvector operator += (pvector const &obj);   

   /**
   * @brief overloaded + operator
   * @param obj vector to add
   * @return sum
   */  
   pvector operator +  (pvector const &obj);

   /**
   * @brief overloaded - operator
   * @param obj vector to substract
   * @return difference
   */  
   pvector operator -  (pvector const &obj);

   /** 
   * @brief overloaded - operator
   * @param obj point to substract
   * @return difference 
   */  
   pvector operator -  (point const &obj);

   /**   
   * @brief overloaded + operator
   * @param obj point to add
   * @return sum 
   */  
   pvector operator +  (point const &obj);

   /**   
   * @brief overloaded == operator
   * @param obj vector to check if equal
   * @return comparison result
   */  
   bool    operator == (pvector const &obj);   

   /**
   * @brief x magnitude of the vector
   */  
   float x;

   /**   
   * @brief y magnitude of the vector
   */  
   float y;
};
