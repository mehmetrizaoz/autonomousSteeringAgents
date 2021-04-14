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
#define PI          3.14159265

using namespace std;

int target_x = -34;
int target_y = 34;
vector<agent *> agents;

float randomNegate(float num){
    if(rand() % 2 == 0) {num *= -1;}
    return num;
}

void updatePosition(agent *ag){
    float angle;
    ag->velocity->add(ag->acceleration);
    ag->velocity->limit(ag->maxSpeed);
    ag->position->add(ag->velocity);
    ag->acceleration->set(0,0);
  
    glPushMatrix();
    glTranslatef(ag->position->x, ag->position->y, 0.0f);   
    
    angle = ag->velocity->y /ag->velocity->x;   
    cout << "velocity " << ag->velocity->x << " " << ag->velocity->y  << endl; 
    cout << "ratio " << angle << endl;        
    angle = atan(angle) * 180 / PI;
    //TODO: following code may be eleminated
    if(ag->velocity->x < 0 && ag->velocity->y < 0)
      angle += 180;
    if(ag->velocity->x < 0 && ag->velocity->y >= 0)
      angle += 180;
    cout << "angle " << angle << endl << endl;
    if(angle <= 360)
       glRotatef(angle, 0.0f, 0.0f, 1.0f);

    glBegin(GL_TRIANGLES);            
    glVertex3f( 1.0f,  0.0f, 0.0f);
    glVertex3f(-1.0f,  0.5f, 0.0f);    
    glVertex3f(-1.0f, -0.5f, 0.0f);
    glEnd();
    glPopMatrix();  
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

//TODO move to agent class
void applyForce(agent *ag){
   //TODO: add mass (MASS has no effect, acc * 1 = force)
   ag->acceleration->add(ag->steering);
}

void seek(agent *ag){     
    ag->desired->set(target_x - ag->position->x, target_y - ag->position->y);    
    //slow down if too close
    if(ag->desired->magnitude() > 2 * ag->r)
       ag->desired->limit(ag->maxSpeed);
    else if(ag->desired->magnitude() > ag->r)
       ag->desired->limit(ag->maxSpeed / 2);
    else
       ag->desired->limit(ag->maxSpeed / 4);
    
    ag->steering = ag->desired;
    ag->steering->sub(ag->velocity);  
    ag->steering->limit(ag->maxForce);
    applyForce(ag);
}

void handleKeypress(unsigned char key, int x, int y) {    
    switch (key) {
        case ESC:
            exit(0);
    }    
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
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){ 
       //target_x = x / 5.88 - 34;
       //target_y = 34 - y / 5.88; 
    }    
}

void mouseMove(int x, int y){
	   target_x = x / 5.88 - 34;
       target_y = 34 - y / 5.88; 
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
    ag1->setVelocity(0.5, 0.4);       
    ag1->setAcceleration(0.01, 0.01);
    agents.push_back(ag1);

    agent *ag2 = new agent(5.5, 16.0);
    ag2->setVelocity(-0.2, 0.4);
    ag2->setAcceleration(0.01, 0.01);
    agents.push_back(ag2);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    
    glutCreateWindow("Autonomous Steering Agents");
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



