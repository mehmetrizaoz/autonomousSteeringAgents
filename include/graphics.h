#pragma once

#include "agent.h"
#include "path.h"

#define WIDTH       34
#define HEIGHT      34


class agent;
class point;

class graphics{
public:
   void drawWall(float border);
   void drawAgent(agent &agent, color &color);
   static void drawLine(point predicted, point normal);
   void drawPath(path &path);  
   static void drawPoint(point p);
   static void drawCircle(point p, float radius);
   void checkInScreen(agent &agent);
   void refreshScene();
   point getMousePosition();
   void initGraphics(int * a, char** c, void (*callback)());
   static void timerEvent(int value);
   static void handleKeypress(unsigned char key, int x, int y);
   static void mouseButton(int button, int state, int x, int y);
   static void handleResize(int w, int h);
   static void mouseMove(int x, int y);   
   static int target_x;
   static int target_y;   
};
