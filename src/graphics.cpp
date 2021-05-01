#include "graphics.h"
#include <GL/glut.h>
#include <iostream>

#define ESC         27

using namespace std;

class path;
class point;

void graphics::initGraphics(){
    glutMouseFunc(graphics::mouseButton);
    glutPassiveMotionFunc(graphics::mouseMove);
    glutKeyboardFunc(graphics::handleKeypress);
    glutReshapeFunc(graphics::handleResize);    
    glutTimerFunc(5, graphics::timerEvent, 0);    
    glutMainLoop();
}

point graphics::getMousePosition(){
    return point (graphics::target_x, graphics::target_y);
}

void graphics::checkInScreen(agent &agent){
    if(agent.position.x > WIDTH)
       agent.position.x -= 2 * WIDTH;
    if(agent.position.x < -WIDTH)
       agent.position.x += 2 * WIDTH;
    if(agent.position.y > HEIGHT)
       agent.position.y -= 2 * HEIGHT;
    if(agent.position.y < -HEIGHT)
       agent.position.y += 2 * HEIGHT;
}

void graphics::mouseMove(int x, int y){
    //TODO: mouse position to glut
    //TODO: magic numbers
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
void graphics::drawPath(path &path){ 
    point p1, p2;
    for(auto it = path.points.begin(); it < path.points.end()-1; it++){
        p1 = point((*it).x, (*it).y - path.width/2) ;
        p2 = point((*(it+1)).x, (*(it+1)).y - path.width/2);
        drawLine(p1, p2);

        p1 = point((*it).x, (*it).y + path.width/2) ;
        p2 = point((*(it+1)).x, (*(it+1)).y + path.width/2);
        drawLine(p1, p2);        
    }
}

void graphics::drawLine(point p1, point p2){
    glColor3f( 0.0, 0.0, 1.0); 
    glLineWidth(2);
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
    point p1 {-border,  border};
    point p2 { border,  border};
    drawLine(p1, p2);

    p1 = point ( border,  border);
    p2 = point ( border, -border);
    drawLine(p1, p2);

    p1 = point (  border, -border);
    p2 = point ( -border, -border);
    drawLine(p1, p2);    

    p1 = point (-border,  border);
    p2 = point (-border, -border);
    drawLine(p1, p2);
}

void graphics::drawAgent(agent &agent, color &color){    
    glPushMatrix();
    glTranslatef(agent.position.x, agent.position.y, 0.0f);  
    glRotatef(agent.velocity.getAngle(), 0.0f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLES);          
    glColor3f( color.R, color.G, color.B);  
    glVertex3f( 1.0f,  0.0f, 0.0f);
    glVertex3f(-1.0f,  0.5f, 0.0f);
    glVertex3f(-1.0f, -0.5f, 0.0f);
    glEnd();
    glPopMatrix();  
}
