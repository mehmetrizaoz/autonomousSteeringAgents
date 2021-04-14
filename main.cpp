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

float theta;
void drawAgent(agent *ag){
    glPushMatrix();
    glTranslatef(ag->position->x, ag->position->y, 0.0f);

    //if(ag->velocity->x != 0 || ag->velocity->y != 0){
       theta = ag->velocity->angle();
    //}    
 
    glRotatef(theta, 0.0f, 0.0f, 1.0f);
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

void updatePosition(agent *ag){    
   ag->velocity->add(ag->acceleration);
   ag->velocity->limit(ag->maxSpeed);
   ag->position->add(ag->velocity);
   ag->acceleration->set(0,0);
  
   drawAgent(ag);
}

void reflect(agent *ag){     
    if(ag->velocity->magnitude() >= ag->maxSpeed)
       ag->setAcceleration(0, 0);
    
    ag->velocity->add(ag->acceleration);

    if ((ag->position->x > WIDTH)  || (ag->position->x < -WIDTH)) {
       ag->velocity->x = ag->velocity->x * -1;
       ag->acceleration->x = ag->acceleration->x * -1;
    }
    if ((ag->position->y > HEIGHT) || (ag->position->y < -HEIGHT)) {
       ag->velocity->y = ag->velocity->y * -1;
       ag->acceleration->y = ag->acceleration->y * -1;
    }        
}

void applyForce(agent *ag){
   ag->steering->div(ag->mass);
   ag->acceleration->add(ag->steering);
}

void seek(agent *ag){     
    ag->desired->set(target_x - ag->position->x, target_y - ag->position->y);    
    
    //slow down
    if(ag->desired->magnitude() > ag->r) { ag->desired->limit(ag->maxSpeed); }
    else if(ag->desired->magnitude() > ag->r / 2) { ag->desired->limit(ag->maxSpeed / 2); }
    else { ag->desired->limit(ag->maxSpeed / 4); }
    
    ag->steering = ag->desired;
    ag->steering->sub(ag->velocity);  
    ag->steering->limit(ag->maxForce);
    applyForce(ag);
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
       seek(*it); 
       //reflect(*it);
       updatePosition(*it);   
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

void setAgent(agent * ag, float s, float f, float r, float m){
    ag->setMaxSpeed(s);
    ag->setMaxForce(f);
    ag->setR(r);
    ag->setMass(m);
    agents.push_back(ag);
}

int main(int argc, char** argv) { 
/*  int numberOfAgents;       
    srand (time(NULL));
    cout << "enter number of agents" << endl;
    cin >> numberOfAgents;
  
    for(int i=0; i<numberOfAgents; i++){   
       //TODO: sometimes generates same point
       agents.push_back(
           new center(randomNegate(float(rand() % 70)), randomNegate(float(rand() % 40))));
    }*/

    agent *ag1 = new agent(0.0, 0.0);
    setAgent(ag1, 0.5, 0.04, 3, 1);

    agent *ag2 = new agent(5.5, 16.0);
    setAgent(ag2, 0.4, 0.03, 4, 1.1);

    agent *ag3 = new agent(0.0, 0.0);
    setAgent(ag3, 0.1, 0.4, 3, 1);

    agent *ag4 = new agent(5.5, 16.0);
    setAgent(ag4, 0.4, 0.33, 4, 1.1);    
    
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
