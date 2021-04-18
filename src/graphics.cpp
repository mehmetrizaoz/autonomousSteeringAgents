#include "graphics.h"
#include <GL/glut.h>

#define ESC         27

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

void graphics::drawWall(int border){
    glBegin(GL_LINES);
    glVertex2f(-border,  border);
    glVertex2f(border, border);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(border,  border);
    glVertex2f(border, -border);
    glEnd();  
    glBegin(GL_LINES);
    glVertex2f(border,  -border);
    glVertex2f(-border, -border);
    glEnd();       
    glBegin(GL_LINES);
    glVertex2f(-border, -border);
    glVertex2f(-border, border);
    glEnd(); 
}

void graphics::drawAgent(float x, float y, float angle){
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
  
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
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
