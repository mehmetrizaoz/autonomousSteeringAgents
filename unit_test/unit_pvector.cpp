#define BOOST_TEST_MODULE pvector_test
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


BOOST_AUTO_TEST_SUITE_END( )

