#pragma once

#include "scenario.h"
#include <vector>

using namespace std;

class pursuit: public scenario{
public:
   pursuit();
   static void loop();  
};

