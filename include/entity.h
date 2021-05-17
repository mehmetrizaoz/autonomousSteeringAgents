#pragma once

#include <string>
#include "color.h"

using namespace std;

class graphics;

class entity{
public:
   entity();
   string name;
   int id;
   color entityColor;

   string getName();
   void setName(string n);
   int getId();
   void setId(int i);

   virtual void draw(graphics view)=0;
};
