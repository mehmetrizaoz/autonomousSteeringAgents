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
   * draws square that consists of 4 lines
   * @brief draws wall
   * @param border position of the wall
   * @param color color of the wall
   */
   void drawWall(float border, color color);

   /**
   * draws agent and rotates it with its velocity
   * @brief drawing agent
   * @param agent agent to draw
   * @param color color of the agent
   */
   void drawAgent(agent &agent, color &color);  

   /**
   * draws line with specified color
   * @brief drawing line
   * @param p1 start point of the line
   * @param p2 end point of the line
   * @param color color of the line
   */
   void drawLine(point p1, point p2, color cl);   

   /**
   * draws path using lines
   * @brief draws path that consists of points
   * @param path path to draw
   * @param color color of the path
   */
   void drawPath(path &path, color color);

   /**
   * draws point using openGL
   * @brief drawing point
   * @param p point to draw
   */
   void drawPoint(point p);

   /**
   * draws circle using openGL
   * @brief drawing circle
   * @param p center of the circle
   * @param radius radius of the circle   
   */
   void drawCircle(point p, float radius);

   /**
   * draws text using openGL
   * @brief drawing text on screen
   * @param p position of the text 
   * @param text text to display   
   */
   void drawText(string text, point p);

   /**
   * makes the agent stay in screen
   * @brief changes agent position if it is out of screen
   * @param agent agent to be in screen
   */
   void forceInScreen(agent &agent);

   /**
   * refresh screen for every existing object
   * @brief position updates for all agents
   */
   void refreshScene();

   /**
   * used to get mouse position
   * @brief gets mouse position
   */
   point getMousePosition();

   /**
   * used to init graphics
   * @brief initialization of graphics
   * @param argv user parameters
   * @param argc count of user parameters
   * @param callback loop function for openGL periodic callback
   */
   void initGraphics(int * argv, char** argc, void (*callback)());

   /**
   * openGL timer event callback
   * @brief periodic timer event function
   * @param value period as ms
   */
   static void timerEvent(int value);

   /**
   * openGL key press event
   * @brief key press event of the openGL
   * @param key key 
   * @param x unused but required for openGL 
   * @param y unused but required for openGL
   */
   static void handleKeypress(unsigned char key, int x, int y);

   /**
   * openGL key mouss press event
   * @brief mouse press event of the openGL
   * @param button mouse button 
   * @param x unused but required for openGL 
   * @param y unused but required for openGL
   */
   static void mouseButton(int button, int state, int x, int y);

   /**
   * openGL screeen resize event
   * @brief event triggered after resizing
   * @param w width of the screen
   * @param h height of the screen
   */
   static void handleResize(int w, int h);

   /**
   * openGL mouse move event
   * @brief event triggered after moving mouse
   * @param x x position of the mouse
   * @param y y position of the mouse
   */
   static void mouseMove(int x, int y);   

   /**
   * holds mouse y position
   * @brief mouse position x
   */
   static int target_x;

   /**
   * holds mouse x position
   * @brief mouse position y
   */
   static int target_y;   
};
