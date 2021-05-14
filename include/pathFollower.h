#pragma once

#include "scenario.h"
#include <vector>

using namespace std;

class pathFollower: public scenario{
public:
   pathFollower();
   static void loop();  
   static path myPath;
   static void createPath(path &p);
};

