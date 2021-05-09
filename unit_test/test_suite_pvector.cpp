#define BOOST_TEST_MODULE test_suite_pvector
#include <boost/test/included/unit_test.hpp>
#include "../include/pvector.h"
#include <iostream>

using namespace std;

BOOST_AUTO_TEST_SUITE (s1) 
 
BOOST_AUTO_TEST_CASE (s1t1){
  pvector p1 = pvector(0, 4);
  pvector p2 = pvector(3, 0);
  pvector p3 = p1 + p2;
  BOOST_CHECK(p3.magnitude() == 5);
}

BOOST_AUTO_TEST_CASE (s1t2){
  pvector p1 = pvector(1, 1);
  p1.mul(3);  
  pvector p2 = pvector(3, 3);
  BOOST_CHECK(p1 == p2);
}

BOOST_AUTO_TEST_CASE (s1t3){
  pvector p1 = pvector(5, 5);
  p1.div(5);  
  pvector p2 = pvector(1, 1);
  BOOST_CHECK(p1 == p2);
}

BOOST_AUTO_TEST_CASE (s1t4){
  pvector p1 = pvector(1, 4);
  pvector p2 = pvector(3, 2);
  float dotProduct = p1.dotProduct(p2);
  BOOST_CHECK(dotProduct == 11);
}

BOOST_AUTO_TEST_CASE (s1t5){
  pvector p1 = pvector(10, 10);
  pvector p2 = pvector(0, 10);
  float angle = p1.angleBetween(p2);
  BOOST_CHECK(angle == 45);
}

BOOST_AUTO_TEST_CASE (s1t6){
  pvector p1 = pvector(3, 4);  
  float angle = p1.getAngle();
  BOOST_CHECK(angle < 53.2 && angle > 52.8);
}

BOOST_AUTO_TEST_CASE (s1t7){
  pvector p1 = pvector(2, 2);
  p1.normalize();  
  float f = 0.707;
  BOOST_CHECK_CLOSE_FRACTION(f, p1.x, 0.01);  
  BOOST_CHECK_CLOSE_FRACTION(f, p1.y, 0.01);

}


BOOST_AUTO_TEST_SUITE_END( )

