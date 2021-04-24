#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "agent.h"
#include "path.h"

class agent;
class point;

class graphics{
public:
   void drawWall(float border);
   void drawAgent(agent &agent);
   void drawLine(point predicted, point normal);
  // void drawSimplePath(point start, point end, int width);
   void drawPath(path &path);  
   void drawPoint(point p);
   void initGraphics();
   static void timerEvent(int value);
   static void handleKeypress(unsigned char key, int x, int y);
   static void mouseButton(int button, int state, int x, int y);
   static void handleResize(int w, int h);
   static void mouseMove(int x, int y);   
   static int target_x;
   static int target_y;   
};

#endif