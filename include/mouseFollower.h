#pragma once

#include "scenario.h"
#include <vector>

using namespace std;

class mouseFollower: public scenario{
public:
   mouseFollower();
   static void loop();  
};

