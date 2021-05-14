#pragma once

#include "scenario.h"
#include <vector>

using namespace std;

class flock: public scenario{
public:
   flock();
   static void loop();  
   void initGL(int* argc, char** argv) override;
};

