/**
 * @file   test_suites.cpp
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  unit test suites
 * @date   15.05.2021
*/

#define BOOST_TEST_MODULE test_suites

#include <boost/test/included/unit_test.hpp>
#include "../include/pvector.h"
#include "../include/point.h"
#include <iostream>

using namespace std;

BOOST_AUTO_TEST_SUITE (s1) 

  /**
  * @brief pvector magnitude test case
  */
  BOOST_AUTO_TEST_CASE (s1t1)
  {
    pvector p1 = pvector(0, 4);
    pvector p2 = pvector(3, 0);
    pvector p3 = p1 + p2;
    BOOST_CHECK(p3.magnitude() == 5);
  }

  /**
  * @brief pvector mul test case
  */
  BOOST_AUTO_TEST_CASE (s1t2)
  {
    pvector p1 = pvector(1, 1);
    p1.mul(3);  
    pvector p2 = pvector(3, 3);
    BOOST_CHECK(p1 == p2);
  }
  
  /**
  * @brief pvector div test case
  */
  BOOST_AUTO_TEST_CASE (s1t3)
  {
    pvector p1 = pvector(5, 5);
    p1.div(5);  
    pvector p2 = pvector(1, 1);
    BOOST_CHECK(p1 == p2);
  }
  
  /**
  * @brief pvector dotproduct test case
  */
  BOOST_AUTO_TEST_CASE (s1t4)
  {
    pvector p1 = pvector(1, 4);
    pvector p2 = pvector(3, 2);
    float dotProduct = p1.dotProduct(p2);
    BOOST_CHECK(dotProduct == 11);
  }
  
  /**
  * @brief pvector angle between vectors test case
  */
  BOOST_AUTO_TEST_CASE (s1t5)
  {
    pvector p1 = pvector(10, 10);
    pvector p2 = pvector(0, 10);
    float angle = p1.angleBetween(p2);
    BOOST_CHECK(angle == 45);
  }
  
  /**
  * @brief pvector get vector angle test case
  */
  BOOST_AUTO_TEST_CASE (s1t6)
  {
    pvector p1 = pvector(3, 4);  
    float angle = p1.getAngle();
    BOOST_CHECK(angle < 53.2 && angle > 52.8);
  }
  
  /**
  * @brief pvector normalize test case
  */
  BOOST_AUTO_TEST_CASE (s1t7)
  {
    pvector p1 = pvector(2, 2);
    p1.normalize();  
    float range = 0.01;
    BOOST_CHECK_CLOSE_FRACTION(0.707, p1.x, range);  
    BOOST_CHECK_CLOSE_FRACTION(0.707, p1.y, range);
  }

  /**
  * @brief pvector limit test case
  */
  BOOST_AUTO_TEST_CASE (s1t8)
  {
    pvector p1 = pvector(2, 2);
    p1.limit(3);
    float range = 0.01;
    BOOST_CHECK_CLOSE_FRACTION(2.12, p1.x, range);  
    BOOST_CHECK_CLOSE_FRACTION(2.12, p1.y, range);
  }

  /**
  * @brief pvector overloaded operators test case
  */
  BOOST_AUTO_TEST_CASE (s1t9)
  {
    pvector p1 = pvector(1, 1);
    p1 += pvector(1,1);
    BOOST_CHECK(p1 == pvector(2,2));
    p1 = pvector(1,1) + pvector(3,3);
    BOOST_CHECK(p1 == pvector(4,4));
    p1 = pvector(4,1) - pvector(3,3);
    BOOST_CHECK(p1 == pvector(1,-2));
    p1 = pvector(4,1) - point(3,3);
    BOOST_CHECK(p1 == pvector(1,-2));
    p1 = pvector(4,1) + point(3,3);
    BOOST_CHECK(p1 == pvector(7,4));
  }

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE (s2) 
  /**
  * @brief point multiplication test case
  */
  BOOST_AUTO_TEST_CASE (s2t1)
  {
    point p1 = point(1, 1);
    p1.mul(3);  
    point p2 = point(3, 3);
    BOOST_CHECK(p1 == p2);
  }

  /**
  * @brief point division test case
  */
  BOOST_AUTO_TEST_CASE (s2t2)
  {
    point p1 = point(4, 4);
    p1.div(4);  
    point p2 = point(1, 1);
    BOOST_CHECK(p1 == p2);
  }

  /**
  * @brief point overloaded operators test case
  */
  BOOST_AUTO_TEST_CASE (s2t3)
  {
    point p1 = point(1,1) + point(3,3);
    BOOST_CHECK(p1 == point(4,4));
    p1 = point(1,1) + pvector(3,3);
    BOOST_CHECK(p1 == point(4,4));
    pvector p2 = point(1,1) - point(3,3);
    BOOST_CHECK(p2 == pvector(-2,-2));
  }

BOOST_AUTO_TEST_SUITE_END()

/**
* @todo unit tests for other classes will be implemented
*/
