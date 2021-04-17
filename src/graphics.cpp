#include "graphics.h"
#include <GL/glut.h>
#include "agent.h"

#define WALL        30

void graphics::drawWall(){
    glBegin(GL_LINES);
    glVertex2f(-WALL,  WALL);
    glVertex2f(WALL, WALL);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(WALL,  WALL);
    glVertex2f(WALL, -WALL);
    glEnd();  
    glBegin(GL_LINES);
    glVertex2f(WALL,  -WALL);
    glVertex2f(-WALL, -WALL);
    glEnd();       
    glBegin(GL_LINES);
    glVertex2f(-WALL,  -WALL);
    glVertex2f(-WALL, WALL);
    glEnd(); 
}

void graphics::drawAgent(agent &ag){
    glPushMatrix();
    glTranslatef(ag.position.x, ag.position.y, 0.0f);
  
    glRotatef(ag.velocity.angle(), 0.0f, 0.0f, 1.0f);
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
