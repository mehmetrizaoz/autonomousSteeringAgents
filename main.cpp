#include <iostream>
#include <stdlib.h> 
#include <GL/glut.h> //https://www.opengl.org/resources/libraries/glut/spec3/node1.html
#include <stdlib.h>
#include <vector>
#include "pvector.h"
#include "agent.h"

using namespace std;
  
vector<agent *> agents;

const int height    = 34;
const int width     = 64;

float randomNegate(float num){
    if(rand() % 2 == 0)
       num *= -1;
    return num;
}

void createAgent(agent *ag){ 
    glPushMatrix();
    glBegin(GL_TRIANGLES); 

    //set new agent position
    if( ag->getMagnitude(ag->getVelocity()) >= 5 ){            
        ag->setAcceleration(0, 0);
    }

    ag->velocity->add(ag->getAcceleration());

    //reflect from screen borders
    if ((ag->getPosition()->x > width)  || (ag->getPosition()->x < -width)) {
       ag->getVelocity()->x = ag->getVelocity()->x * -1;
       ag->getAcceleration()->x = ag->getAcceleration()->x * -1;
    }
    if ((ag->getPosition()->y > height) || (ag->getPosition()->y < -height)) {
       ag->getVelocity()->y = ag->getVelocity()->y * -1;
       ag->getAcceleration()->y = ag->getAcceleration()->y * -1;
    }
  
    ag->position->add(ag->getVelocity());
    //cout << "pos " << ag->position->x << " " << ag->position->y << endl;
    //cout << "vel " << ag->velocity->x << " " << ag->velocity->y << endl;
    //cout << "acc " << ag->acceleration->x << " " << ag->acceleration->y << endl << endl;
        
    //draw agent
    glVertex3f( ag->getPosition()->x - 0.29f, ag->getPosition()->y - 0.50f, 0.00f);
    glVertex3f( ag->getPosition()->x - 0.29f, ag->getPosition()->y + 0.50f, 0.00f);
    glVertex3f( ag->getPosition()->x + 0.57f, ag->getPosition()->y        , 0.00f);
    glEnd();
    glPopMatrix();   
}

void handleKeypress(unsigned char key, int x, int y) {    
    switch (key) {
        case 27: //Escape key
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
       createAgent(*it);       
    }
   
    glutSwapBuffers();
}

void update(int value) {
    glutPostRedisplay(); //Tell GLUT that the display has changed
    glutTimerFunc(25, update, 0);
}

void mouseButton(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		cout << "x: " << x << " " << "y: " << y << endl;
	}
}

void mouseMove(int x, int y){
 	cout << "x: " << x << " " << "y: " << y << endl;
}

int main(int argc, char** argv) { 
/*  int numberOfAgents;       
    srand (time(NULL));
    cout << "enter number of agents" << endl;
    cin >> numberOfAgents;
  
    for(int i=0; i<numberOfAgents; i++){   
       //TODO: generating same point is possible
       agents.push_back(
           new center(randomNegate(float(rand() % 70)), randomNegate(float(rand() % 40))));
    }*/

    agent *ag1 = new agent(0.0, 0.0);
    ag1->setVelocity(0.5, 0.5);
    ag1->setAcceleration(0.01, 0.01);
    agents.push_back(ag1);
    
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



