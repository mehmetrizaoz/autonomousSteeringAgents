/**
 * @file   graphics.cpp
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  graphics class implementation
 * @date   15.05.2021
*/

#include "graphics.h"
#include <GL/glut.h>
#include <iostream>
#include "math.h"

using namespace std;

class path;
class point;

int graphics::target_x = -WIDTH;
int graphics::target_y = HEIGHT;

point graphics::clickPosition;
bool graphics::clicked = false;

void graphics::drawText(string text, point p)
{
   glColor3f (0.0, 0.0, 1.0);
   glRasterPos2f(p.x, p.y);
   for ( string::iterator it=text.begin(); it!=text.end(); ++it){ 
      glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *it);
   }   
}

void graphics::refreshScene()
{
   glutSwapBuffers();
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    
   glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
   glLoadIdentity(); //Reset the drawing perspective    
   glTranslatef(0.0f, 0.0f, -85.0f); //Move to the center of the triangle     
}

void graphics::initGraphics(int * argv, char** argc, void (*callback)())
{
   glutInit(argv, argc);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(400, 400);   
   glutCreateWindow("Autonomous Steering Agents");
   glClearColor(0.7f, 0.7f, 0.7f, 1.0f); //set background color
   glEnable(GL_DEPTH_TEST);   
   glutDisplayFunc(*callback);
   glutMouseFunc(graphics::mouseButton);
   glutPassiveMotionFunc(graphics::mouseMove);
   glutKeyboardFunc(graphics::handleKeypress);
   glutReshapeFunc(graphics::handleResize);    
   glutTimerFunc(20, graphics::timerEvent, 0);    
   glutMainLoop();
}

point graphics::getMousePosition()
{
   return point (graphics::target_x, graphics::target_y);
}

void graphics::forceInScreen(agent &agent)
{
    if(agent.position.x > WIDTH)
       agent.position.x -= 2 * WIDTH;
    if(agent.position.x < -WIDTH)
       agent.position.x += 2 * WIDTH;
    if(agent.position.y > HEIGHT)
       agent.position.y -= 2 * HEIGHT;
    if(agent.position.y < -HEIGHT)
       agent.position.y += 2 * HEIGHT;
}

void graphics::mouseMove(int x, int y)
{    
	graphics::target_x = x / 5.88 - 34;
    graphics::target_y = 34 - y / 5.88; 
}

void graphics::handleResize(int w, int h)
{
    glViewport(0, 0, w, h);  //Tell OpenGL how to convert from coordinates to pixel values
    glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective       
    glLoadIdentity(); //Reset the camera
    //Set the camera perspective
    gluPerspective(45.0,                  //The camera angle
                   (double)w / (double)h, //The width-to-height ratio
                   1.0,                   //The near z clipping coordinate
                   200.0);                //The far z clipping coordinate
}

void graphics::timerEvent(int value)
{
    glutPostRedisplay(); //Tell GLUT that the display has changed
    glutTimerFunc(value, timerEvent, 20);
}

void graphics::mouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        clicked = true;
        clickPosition.x = x / 5.88 - 34;
        clickPosition.y = 34 - y / 5.88;
    }    
}

void graphics::handleKeypress(unsigned char key, int x, int y)
{
    if (key == ESC){ 
        exit(0); 
    }
}

void graphics::drawPath(path &path)
{
    point p1, p2;    
    for(auto it = path.points.begin(); it < path.points.end()-1; it++){
        p1 = point((*it).x, (*it).y - path.getPathWidth() / 2) ;
        p2 = point((*(it+1)).x, (*(it+1)).y - path.getPathWidth() / 2);
        drawLine(p1, p2, path.getColor());

        p1 = point((*it).x, (*it).y + path.getPathWidth() / 2) ;
        p2 = point((*(it+1)).x, (*(it+1)).y + path.getPathWidth() / 2);
        drawLine(p1, p2, path.getColor());        
    }
}

void graphics::drawLine(point p1, point p2, color cl) 
{
    glColor3f( cl.R, cl.G, cl.B); 
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glEnd();  
}

void graphics::drawCircle(point p, float radius, color color)
{ 
   glColor3f(color.R, color.G, color.B); 
   glBegin(GL_LINE_STRIP);                              
   glLineWidth(2);
   for (int i = 0; i <= 300; i++) {
     float angle = 2 * PI * i / 300;
     float x = cos(angle) * radius;
     float y = sin(angle) * radius;
     glVertex2d(p.x + x, p.y + y);
   }
   glEnd();
}

void graphics::drawPoint(point p ,color cl)
{
    glColor3f(cl.R, cl.G, cl.B); 
    glPointSize(4.0);
    glBegin(GL_POINTS);
    glVertex2f(p.x, p.y);
    glEnd();
}

void graphics::drawAgent(agent &agent)
{
    glPushMatrix();
    glTranslatef(agent.position.x, agent.position.y, 0.0f);  
    glRotatef(agent.getVelocity().getAngle(), 0.0f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLES);          
    glColor3f( agent.getColor().R, agent.getColor().G, agent.getColor().B);  
    glVertex3f( 1.0f,  0.0f, 0.0f);
    glVertex3f(-1.0f,  0.5f, 0.0f);
    glVertex3f(-1.0f, -0.5f, 0.0f);
    glEnd();
    glPopMatrix();  
}
