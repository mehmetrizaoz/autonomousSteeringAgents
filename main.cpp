#include <iostream>
#include <GL/glut.h> 
#include <vector>
#include "pvector.h"
#include "agent.h"
#include "point.h"
#include "graphics.h"
#include "flowField.h"

#define WIDTH       34
#define HEIGHT      34

#define WALL        30
#define DISTANCE    2

#define SEEK          1 //mouse follower
#define REFLECT       2 //apply force only near the wall
#define WIND          3 //wind force (no other force)
#define PATH_FOLLOWER 4

using namespace std;

int mode;

flowField flow;
graphics view;
vector<agent *> agents;

int graphics::target_x = -WIDTH;
int graphics::target_y = HEIGHT;

//TODO: move to agent class
void updatePosition(agent &ag){   
   //out << "acc " << ag.acceleration.x << " " <<  ag.acceleration.y << endl << endl;
   ag.velocity = ag.velocity + ag.acceleration; 
   ag.velocity.limit(ag.maxSpeed);
   //cout << "vel " << ag.velocity.x     << " " <<  ag.velocity.y     << endl;
   ag.position.x = ag.position.x + ag.velocity.x;
   ag.position.y = ag.position.y + ag.velocity.y;
   //cout << "pos " << ag.position.x     << " " <<  ag.position.y     << endl;
   ag.acceleration = pvector(0,0);
  
   view.drawAgent(ag.position.x, ag.position.y, ag.velocity.getAngle());
}

//TODO: move to agent class
void reflect(agent &ag){    
    view.drawWall(WALL);
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

void drawPath(point start, point end, float width){   
    view.drawLine(start.x, start.y - width/2, end.x, end.y - width/2);
    view.drawLine(start.x, start.y + width/2, end.x, end.y + width/2);
}

//TODO: move to agent class
void seek(agent &ag){
    ag.desired = ag.targetPoint - ag.position;
    
    //arriving behavior
    if(ag.desired.magnitude() > ag.r) { ag.desired.limit(ag.maxSpeed); }
    else { ag.desired.limit(ag.maxSpeed / 2); }
    
    ag.steering = ag.desired;
    ag.steering = ag.steering - ag.velocity;  
    ag.steering.limit(ag.maxForce);
    ag.force = ag.steering;
    ag.applyForce();
}

//TODO: move to agent class
void followPath(agent &ag){
  int pathWidth = 1;
  int slope = 40; //TODO: make this degree
  point start = point(-WIDTH - 5,  HEIGHT - slope);
  point end   = point( WIDTH + 5, -HEIGHT + slope);
  drawPath(start, end, 5);

  pvector predict = ag.velocity;
  point predictedPos = point();
  predictedPos = ag.position + predict;
  
  pvector b = end - start;
  pvector a = predictedPos - start;

  b.normalize();
  pvector b_normalized = b;
  float a_dot_b = a.dotProduct(b);
  
  b.mul(a_dot_b);
  point normalPoint = start + b;
  pvector distance = predictedPos - normalPoint;
  ag.targetPoint = normalPoint + b_normalized;
  
  
  /*glBegin(GL_LINES);
  glVertex2f(predictedPos.x, predictedPos.y);
  glVertex2f(normalPoint.x, normalPoint.y);
  glEnd();  

  glPointSize(2.2);
  glBegin(GL_POINTS);
  glVertex2f(ag.target.x, ag.target.y);
  glEnd();*/
    
  if(distance.magnitude() > pathWidth / 2){
     seek(ag);
  }
  
}

//TODO: move to agent class
void wind(agent &ag){
    //pos_x, pos_y must be non negative integer
    int pos_x = abs((int)ag.position.x) % WIDTH;
    int pos_y = abs((int)ag.position.y) % HEIGHT;
    
    //TODO: modification required for non uniform fields
    ag.force = flow.getField(pos_x, pos_y); 
    //cout << "force " << ag.force.x  << " " <<  ag.force.y     << endl;
    ag.applyForce();
}

//TODO: move to graphics class
void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    
    glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
    glLoadIdentity(); //Reset the drawing perspective    
    glTranslatef(0.0f, 0.0f, -85.0f); //Move to the center of the triangle    
    
    for(auto it = agents.begin(); it < agents.end(); it++){ 
       switch(mode){
           case SEEK:       
              (**it).targetPoint.x = graphics::target_x;
              (**it).targetPoint.y = graphics::target_y;
              seek(**it);       
           break;
           case REFLECT:       reflect(**it);    break; //velocity must be non zero                       
           case WIND:          wind(**it);       break;
           case PATH_FOLLOWER: followPath(**it); break;
       }
       updatePosition(**it);   
    }

    glutSwapBuffers();
}

int main(int argc, char** argv) {    
    cout << "enter mode please:\nSEEK:1\nREFLECT:2\nWIND:3\nPATH FOLLOWER:4\n\n";
    cin >> mode;

    view = graphics();
    flow = flowField();

    agent ag1 = agent(-30, 20.0);    
    agent ag2 = agent(-20.5, 20.0);
    agent ag3 = agent(-10.5, 0.0);
    agent ag4 = agent(-34.5, -16.0);    
    ag1.setFeatures(0.2,  0.05, 0.5, 1);
    ag2.setFeatures(0.1,  0.04, 0.5, 1);
    ag3.setFeatures(0.15, 0.03, 0.5, 1);
    ag4.setFeatures(0.25, 0.02, 0.5, 1); 
    agents.push_back(&ag1);
    agents.push_back(&ag2);
    agents.push_back(&ag3);
    agents.push_back(&ag4);
       
    //TODO: move to graphics class
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);    
    glutCreateWindow("Autonomous Steering Agents");
    glClearColor(0.7f, 0.9f, 1.0f, 1.0f); //set background color
    glEnable(GL_DEPTH_TEST);    
    glutDisplayFunc(drawScene);

    view.initGraphics();

    return 0;
}
