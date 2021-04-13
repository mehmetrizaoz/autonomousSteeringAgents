#include <iostream>
#include <stdlib.h> 
#include <GL/glut.h> //https://www.opengl.org/resources/libraries/glut/spec3/node1.html
#include <stdlib.h>
#include <vector>
#include "pvector.h"
#include "agent.h"

#define MAX_SPEED   1
#define MAX_FORCE   1
#define WIDTH       34
#define HEIGHT      34
#define ESC         27
#define MASS        1

using namespace std;

int target_x = -34;
int target_y = 34;
vector<agent *> agents;

float randomNegate(float num){
    if(rand() % 2 == 0)
       num *= -1;
    return num;
}

void updatePosition(agent *ag){
    //TODO: drawing will be done regarding velocity vector
    ag->velocity->add(ag->acceleration);
    ag->velocity->limit(MAX_SPEED);
    ag->position->add(ag->velocity);
    ag->acceleration->set(0,0);

    glPushMatrix();
    glBegin(GL_TRIANGLES);
    glVertex3f( ag->position->x - 0.29f, ag->position->y - 0.50f, 0.00f);
    glVertex3f( ag->position->x - 0.29f, ag->position->y + 0.50f, 0.00f);
    glVertex3f( ag->position->x + 0.57f, ag->position->y        , 0.00f);
    glEnd();
    glPopMatrix();  
}

void reflect(agent *ag){     
    if(pvector::getMagnitude(ag->velocity) >= MAX_SPEED)
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
   //MASS has no effect
   ag->acceleration->add(ag->steering);
}

void seek(agent *ag){     
    ag->desired->set(target_x - ag->position->x, target_y - ag->position->y);    
    ag->desired->limit(MAX_SPEED);
    
    ag->steering = ag->desired;
    ag->steering->sub(ag->velocity);  
    ag->steering->limit(MAX_FORCE);
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

void update(int value) {
    glutPostRedisplay(); //Tell GLUT that the display has changed
    glutTimerFunc(25, update, 0);
}

void mouseButton(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		//cout << "x: " << x << " " << "y: " << y << endl;

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

    /*agent *ag2 = new agent(1.5, 6.0);
    ag2->setVelocity(-0.2, 0.4);
    ag2->setAcceleration(0.01, 0.01);
    agents.push_back(ag2);*/
    
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
    
    glutTimerFunc(25, update, 0);    
    glutMainLoop();
    return 0;
}



