#include <iostream>
#include <stdlib.h> 
#include <GL/glut.h> //https://www.opengl.org/resources/libraries/glut/spec3/node1.html
#include <stdlib.h>
#include <vector>
#include "pvector.h"
#include "agent.h"
#include "math.h"

#define WIDTH       34
#define HEIGHT      34

#define ESC         27

using namespace std;

int target_x = -WIDTH;
int target_y = HEIGHT;
vector<agent *> agents;

float randomNegate(float num){
    if(rand() % 2 == 0) {num *= -1;}
    return num;
}

void drawAgent(agent &ag){
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
/*
void updatePosition(agent &ag){   
   ag.velocity = ag.velocity + ag.acceleration; 
   ag.velocity.limit(ag.maxSpeed);
   ag.position = ag.position + ag.velocity;
   ag.acceleration = pvector(0,0);   
}*/

void reflect(agent &ag){     
    if(ag.velocity.magnitude() >= ag.maxSpeed)
       ag.acceleration = pvector (0, 0);
    
    ag.velocity = ag.velocity + ag.acceleration;

    if ((ag.position.x > WIDTH)  || (ag.position.x < -WIDTH)) {
       ag.velocity.x = ag.velocity.x * -1;
       ag.acceleration.x = ag.acceleration.x * -1;
    }
    if ((ag.position.y > HEIGHT) || (ag.position.y < -HEIGHT)) {
       ag.velocity.y = ag.velocity.y * -1;
       ag.acceleration.y = ag.acceleration.y * -1;
    }        
}

void seek(agent &ag){
    ag.desired = pvector(target_x - ag.position.x, target_y - ag.position.y);    
    
    //slow down
    if(ag.desired.magnitude() > ag.r) { ag.desired.limit(ag.maxSpeed); }
    else if(ag.desired.magnitude() > ag.r / 2) { ag.desired.limit(ag.maxSpeed / 2); }
    else { ag.desired.limit(ag.maxSpeed / 4); }
    
    ag.steering = ag.desired;
    ag.steering = ag.steering - ag.velocity;  
    ag.steering.limit(ag.maxForce);
    ag.applyForce();
}

void handleKeypress(unsigned char key, int x, int y) {    
    if (key == ESC) { exit(0); }    
}

void handleResize(int w, int h) {        
    glViewport(0, 0, w, h);  //Tell OpenGL how to convert from coordinates to pixel values
    glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective       
    glLoadIdentity(); //Reset the camera
    //Set the camera perspective
    gluPerspective(45.0,                  //The camera angle
                   (double)w / (double)h, //The width-to-height ratio
                   1.0,                   //The near z clipping coordinate
                   200.0);                //The far z clipping coordinate
}

void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    
    glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
    glLoadIdentity(); //Reset the drawing perspective    
    glTranslatef(0.0f, 0.0f, -85.0f); //Move to the center of the triangle    
    
    for(auto it = agents.begin(); it < agents.end(); it++){       
       seek(**it); 
       //reflect(**it);
       (**it).updatePosition();
       drawAgent(**it);
    }
   
    glutSwapBuffers();
}

void timerEvent(int value) {
    glutPostRedisplay(); //Tell GLUT that the display has changed
    glutTimerFunc(5, timerEvent, 0);
}

void mouseButton(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){}    
}

void mouseMove(int x, int y){
    //TODO: mouse position to glut
	target_x = x / 5.88 - WIDTH;
    target_y = HEIGHT - y / 5.88; 
}

int main(int argc, char** argv) {     
    agent ag1  = agent(0.0, 0.0, 0.5, 0.043, 3, 1);
    agents.push_back(&ag1);

    agent ag2 = agent(5.5, 16.0, 0.4, 0.032, 4, 1.1);
    agents.push_back(&ag2);

    agent ag3 = agent(0.5, 4.0, 0.3, 0.41, 3, 1);
    agents.push_back(&ag3);
    
    agent ag4 = agent(5.5, 16.0, 0.44, 0.33, 4, 1.1); 
    agents.push_back(&ag4);   
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    
    glutCreateWindow("Autonomous Steering Agents");
    glClearColor(0.7f, 0.9f, 1.0f, 1.0f); //set background color
    glEnable(GL_DEPTH_TEST);
    
    glutDisplayFunc(drawScene);
    glutMouseFunc(mouseButton);
    glutPassiveMotionFunc(mouseMove);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);
    
    glutTimerFunc(5, timerEvent, 0);    
    glutMainLoop();
    return 0;
}
