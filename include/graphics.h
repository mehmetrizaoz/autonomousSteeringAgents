#pragma once

#include "agent.h"
#include "path.h"

#define WIDTH       34
#define HEIGHT      34

#define ESC         27
#define PI          3.14159265

class agent;
class point;

class graphics{
public:
   void drawWall(float border);
   void drawAgent(agent &agent, color &color);  
   void drawLine(point p1, point p2, color cl);
   void drawPath(path &path);  
   void drawPoint(point p);
   static void drawCircle(point p, float radius);
   void checkInScreen(agent &agent);
   void drawText(string text, point p);
   void refreshScene();
   point getMousePosition();
   void initGraphics(int * argv, char** argc, void (*callback)());
   static void timerEvent(int value);
   static void handleKeypress(unsigned char key, int x, int y);
   static void mouseButton(int button, int state, int x, int y);
   static void handleResize(int w, int h);
   static void mouseMove(int x, int y);   
   static int target_x;
   static int target_y;   
};
