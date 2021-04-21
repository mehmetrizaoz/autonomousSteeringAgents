#ifndef PATH_H
#define PATH_H

#include "point.h"

class path{
public:
   point start;
   point end;  
   int width; 
   path(point start, point end, int width);
   path();   
};

#endif
