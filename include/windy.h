#pragma once

#include "scenario.h"
#include "flowField.h"
#include <vector>

using namespace std;

class windy: public scenario{
public:
   windy();
   static void loop();  
   static flowField flow;
};

