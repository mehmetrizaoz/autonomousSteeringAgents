#pragma once

#include "scenario.h"
#include <vector>

using namespace std;

class wander: public scenario{
public:
   wander();
   static void loop();  
   void initGL(int* argc, char** argv) override;
};

