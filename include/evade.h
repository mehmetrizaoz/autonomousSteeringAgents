#pragma once

#include "scenario.h"
#include <vector>

using namespace std;

class evade: public scenario{
public:
   evade();
   static void loop();  
   void initGL(int* argc, char** argv) override;
};

