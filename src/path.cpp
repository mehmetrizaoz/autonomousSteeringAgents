#include "point.h"
#include "path.h"


path::path(point start, point end, int width){
   this->start = start;
   this->end   = end;
   this->width = width;
}

path::path(){}