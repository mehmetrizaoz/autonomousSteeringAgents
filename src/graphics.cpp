#include "graphics.h"
#include "agent.h"
#include "path.h"
#include <GL/glut.h>

#define ESC         27

void graphics::initGraphics(){
    glutMouseFunc(graphics::mouseButton);
    glutPassiveMotionFunc(graphics::mouseMove);
    glutKeyboardFunc(graphics::handleKeypress);
    glutReshapeFunc(graphics::handleResize);    
    glutTimerFunc(5, graphics::timerEvent, 0);    
    glutMainLoop();
}

void graphics::drawPath(point start, point end, int width){   
    drawLine(start.x, start.y - width/2, end.x, end.y - width/2);
    drawLine(start.x, start.y + width/2, end.x, end.y + width/2);
}

void graphics::mouseMove(int x, int y){
    //TODO: mouse position to glut
	graphics::target_x = x / 5.88 - 34;
    graphics::target_y = 34 - y / 5.88; 
}

void graphics::handleResize(int w, int h) {        
    glViewport(0, 0, w, h);  //Tell OpenGL how to convert from coordinates to pixel values
    glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective       
    glLoadIdentity(); //Reset the camera
    //Set the camera perspective
    gluPerspective(45.0,                  //The camera angle
                   (double)w / (double)h, //The width-to-height ratio
                   1.0,                   //The near z clipping coordinate
                   200.0);                //The far z clipping coordinate
}

void graphics::timerEvent(int value) {
    glutPostRedisplay(); //Tell GLUT that the display has changed
    glutTimerFunc(20, timerEvent, 0);
}

void graphics::mouseButton(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){}    
}

void graphics::handleKeypress(unsigned char key, int x, int y) {    
    if (key == ESC){ exit(0); }
}

//TODO: delete this function, use the other one for both operation
void graphics::drawLine(float p1_x, float p1_y, float p2_x, float p2_y){
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(p1_x, p1_y);
    glVertex2f(p2_x, p2_y);
    glEnd();
}

void graphics::drawLine(point p1, point p2){
  glBegin(GL_LINES);
  glVertex2f(p1.x, p1.y);
  glVertex2f(p2.x, p2.y);
  glEnd();  
}

void graphics::drawPoint(point p){
  glPointSize(2.2);
  glBegin(GL_POINTS);
  glVertex2f(p.x, p.y);
  glEnd();
}

void graphics::drawWall(float border){
    drawLine(-border,  border,  border,  border);
    drawLine( border,  border,  border, -border);
    drawLine( border, -border, -border, -border);
    drawLine(-border, -border, -border,  border);
}

void graphics::drawAgent(agent &agent){    
    glPushMatrix();
    glTranslatef(agent.position.x, agent.position.y, 0.0f);  
    glRotatef(agent.velocity.getAngle(), 0.0f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLES);          
    glColor3f(1.0f, 0.7f, 0.0f);  
    glVertex3f( 1.0f,  0.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f,  0.5f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f); 
    glVertex3f(-1.0f, -0.5f, 0.0f);
    glEnd();
    glPopMatrix();  
}
