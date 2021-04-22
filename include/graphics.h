#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "agent.h"
#include "path.h"

class graphics{
public:
   void drawWall(float border);
   void drawAgent(agent &agent);
   void drawLine(point predicted, point normal);
   void drawPath(point start, point end, int width);
   void drawPoint(point p);
   void initGraphics();
   static void timerEvent(int value);
   static void handleKeypress(unsigned char key, int x, int y);
   static void mouseButton(int button, int state, int x, int y);
   static void handleResize(int w, int h);
   static void mouseMove(int x, int y);   
   static int target_x;
   static int target_y;   
private:
   void drawLine(float p1_x, float p1_y, float p2_x, float p2_y);
};

#endif