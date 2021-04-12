#include <iostream>
#include <stdlib.h> 
#include <GL/glut.h> //https://www.opengl.org/resources/libraries/glut/spec3/node1.html
#include <stdlib.h>
#include <vector>
#include "pvector.h"
#include "agent.h"

#define SPEED_LIMIT 10
#define WIDTH       34
#define HEIGHT      34
#define ESC         27

using namespace std;

int mousePos_x;
int mousePos_y;
vector<agent *> agents;

float randomNegate(float num){
    if(rand() % 2 == 0)
       num *= -1;
    return num;
}

void drawAgent(agent *ag){
    //TODO: drawing will be done regarding velocity vector
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    glVertex3f( ag->position->x - 0.29f, ag->position->y - 0.50f, 0.00f);
    glVertex3f( ag->position->x - 0.29f, ag->position->y + 0.50f, 0.00f);
    glVertex3f( ag->position->x + 0.57f, ag->position->y        , 0.00f);
    glEnd();
    glPopMatrix();  
}

void updateAgentPosition(agent *ag){      
    ag->calculateDirection(mousePos_x / 5.88 - 34, 34 - mousePos_y / 5.88);   
    ag->setAcceleration(pvector::getNormal(ag->direction));  
    ag->velocity->add(ag->acceleration);
    ag->limitVelocity();


/*
    if(pvector::getMagnitude(ag->getVelocity()) >= SPEED_LIMIT)
       ag->setAcceleration(0, 0);

    ag->velocity->add(ag->getAcceleration());
    //reflect from screen borders
    if ((ag->getPosition()->x > WIDTH)  || (ag->getPosition()->x < -WIDTH)) {
       ag->getVelocity()->x = ag->getVelocity()->x * -1;
       ag->getAcceleration()->x = ag->getAcceleration()->x * -1;
    }
    if ((ag->getPosition()->y > HEIGHT) || (ag->getPosition()->y < -HEIGHT)) {
       ag->getVelocity()->y = ag->getVelocity()->y * -1;
       ag->getAcceleration()->y = ag->getAcceleration()->y * -1;
    }
    */
    ag->position->add(ag->velocity);
    drawAgent(ag);
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
       updateAgentPosition(*it);       
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
	   mousePos_x = x;
       mousePos_y = y;
    }    
}

void mouseMove(int x, int y){

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
/*
    agent *ag2 = new agent(1.5, 6.0);
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



