#include <iostream>
#include <stdlib.h> 
#include <GL/glut.h> //https://www.opengl.org/resources/libraries/glut/spec3/node1.html
#include <stdlib.h>
#include <vector>
#include "pvector.h"
#include "agent.h"
#include "math.h"
#include "flowField.h"

//platform
#define WIDTH       34
#define HEIGHT      34
//reflection
#define WALL        30
#define DISTANCE    2
//keys
#define ESC         27
//
#define SEEK        1 //mouse follower
#define REFLECT     2 //apply force only near the wall
#define WIND        3 //wind force (no other force)

using namespace std;

//mode
int mode;
//mouse coordinates
int target_x = -WIDTH;
int target_y = HEIGHT;

flowField flow;
vector<agent *> agents;

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

void updatePosition(agent &ag){   
   cout << "acc " << ag.acceleration.x << " " <<  ag.acceleration.y << endl << endl;
   ag.velocity = ag.velocity + ag.acceleration; 
   ag.velocity.limit(ag.maxSpeed);
   cout << "vel " << ag.velocity.x     << " " <<  ag.velocity.y     << endl;
   ag.position = ag.position + ag.velocity;
   cout << "pos " << ag.position.x     << " " <<  ag.position.y     << endl;
   ag.acceleration = pvector(0,0);
  
   drawAgent(ag);
}

//TODO: move opengl related code to platform (not exist) class
void drawWall(){
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

void reflect(agent &ag){    
    drawWall();
    int turnPoint = WALL - DISTANCE; 
    
    if(ag.position.x >= turnPoint){
       ag.desired = pvector( -ag.maxSpeed, ag.velocity.y );
       ag.steering = ag.desired - ag.velocity;
       ag.steering.limit(ag.maxForce);
       ag.force = ag.steering;
       ag.applyForce();
    }
    else if(ag.position.x <= -turnPoint){
       ag.desired = pvector( ag.maxSpeed, ag.velocity.y );
       ag.steering = ag.desired - ag.velocity;
       ag.steering.limit(ag.maxForce);
       ag.force = ag.steering;
       ag.applyForce();
    }
    else if(ag.position.y >= turnPoint){
       ag.desired = pvector( ag.velocity.x, -ag.maxSpeed );
       ag.steering = ag.desired - ag.velocity;
       ag.steering.limit(ag.maxForce);
       ag.force = ag.steering;
       ag.applyForce();
    }
    else if(ag.position.y <= -turnPoint){
       ag.desired = pvector( ag.velocity.x, ag.maxSpeed );
       ag.steering = ag.desired - ag.velocity;
       ag.steering.limit(ag.maxForce);
       ag.force = ag.steering;
       ag.applyForce();
    }
}

void wind(agent &ag){
    //pos_x, pos_y must be non negative integer
    int pos_x = abs((int)ag.position.x) % WIDTH;
    int pos_y = abs((int)ag.position.y) % HEIGHT;
    
    //TODO: modification required for perlin noise fields
    ag.force = flow.getField(pos_x, pos_y); 
    cout << "for " << ag.force.x  << " " <<  ag.force.y     << endl;

    ag.applyForce();
}

void seek(agent &ag){
    ag.desired = pvector(target_x - ag.position.x, target_y - ag.position.y);    
    //arriving behavior
    if(ag.desired.magnitude() > ag.r) { ag.desired.limit(ag.maxSpeed); }
    else { ag.desired.limit(ag.maxSpeed / 2); }
    
    ag.steering = ag.desired;
    ag.steering = ag.steering - ag.velocity;  
    ag.steering.limit(ag.maxForce);
    ag.force = ag.steering;
    ag.applyForce();
}

void handleKeypress(unsigned char key, int x, int y) {    
    if (key == ESC){ exit(0); }
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
       switch(mode){
           case SEEK:
              seek(**it); 
           break;
           case REFLECT:
              //velocity must be non zero 
              //(there is no force, space behavior except near the wall)
              reflect(**it); 
           break;
           case WIND:
              wind(**it); 
           break;
       }

       updatePosition(**it);   
    }
   
    glutSwapBuffers();
}

void timerEvent(int value) {
    glutPostRedisplay(); //Tell GLUT that the display has changed
    glutTimerFunc(20, timerEvent, 0);
}

void mouseButton(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){}    
}

void mouseMove(int x, int y){
    //TODO: mouse position to glut
	target_x = x / 5.88 - WIDTH;
    target_y = HEIGHT - y / 5.88; 
}

//TODO: move to agent class
void setAgent(agent &ag, float s, float f, float r, float m){
    ag.setMaxSpeed(s);
    ag.setMaxForce(f);
    ag.setR(r);
    ag.setMass(m);
    agents.push_back(&ag);
}

int main(int argc, char** argv) {    
    cout << "enter mode pleas:\nSEEK:1\nREFLECT:2\nWIND:3"<< endl;
    cin >> mode;

    flow = flowField();

    agent ag1 = agent(1.5, 0.0);
    setAgent(ag1, 2, 0.4, 3, 1);
/*
    agent ag2 = agent(0.5, 2.0);
    setAgent(ag2, 0.3, 0.04, 4, 1.1);

    agent ag3 = agent(0.5, 4.0);
    setAgent(ag3, 0.3, 0.03, 3, 1);

    agent ag4 = agent(0.5, 16.0);
    setAgent(ag4, 0.44, 0.33, 4, 1.1); */
    
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
