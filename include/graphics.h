/**
 * @file   graphics.h
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  graphics class, drives openGL
 * @date   15.05.2021
*/

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
   /**   
   * @brief drawing with corresponding angle
   * @param agent instance to change
   */
   void drawAgent(agent &agent);  

   /**
   * @brief drawing line
   * @param p1 start point of the line
   * @param p2 end point of the line
   * @param color of the line
   */
   void drawLine(point p1, point p2, color cl);   

   /**
   * @brief draws path
   * @param path to draw
   */
   void drawPath(path &path);

   /**
   * @brief draws point
   * @param p point to draw
   */
   void drawPoint(point p);

   /**   
   * @brief draws circle
   * @param p center of the circle
   * @param radius radius of the circle   
   */
   void drawCircle(point p, float radius);

   /**
   * @brief draws text on screen
   * @param p position of the text 
   * @param text to display   
   */
   void drawText(string text, point p);

   /**
   * @brief changes agent position so that it stays in screen
   * @param agent instance
   */
   void forceInScreen(agent &agent);

   /**
   * @brief update agent position
   */
   void refreshScene();

   /**
   * @brief gets mouse position
   * @return mouse point
   */
   point getMousePosition();

   /**
   * @brief initialization of graphics
   * @param argv user parameters
   * @param argc count of user parameters
   * @param callback loop function for openGL periodic callback
   */
   void initGraphics(int * argv, char** argc, void (*callback)());

   /**
   * @brief periodic timer event
   * @param value period as ms
   */
   static void timerEvent(int value);

   /**
   * @brief key press event
   * @param key pressed
   * @param x unused but required for openGL 
   * @param y unused but required for openGL
   */
   static void handleKeypress(unsigned char key, int x, int y);

   /**
   * @brief mouse press event
   * @param button mouse key pressed
   * @param state down/up etc.
   * @param x unused but required for openGL 
   * @param y unused but required for openGL
   */
   static void mouseButton(int button, int state, int x, int y);

   /**
   * @brief event triggered with screen resizing
   * @param w width of the screen
   * @param h height of the screen
   */
   static void handleResize(int w, int h);

   /**
   * @brief event triggered with mouse movements
   * @param x osition of the mouse
   * @param y position of the mouse
   */
   static void mouseMove(int x, int y);   

   /**
   * @brief mouse position x
   */
   static int target_x;

   /**
   * @brief mouse position y
   */
   static int target_y;   
};
