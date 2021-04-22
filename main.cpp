#include <iostream>
#include <GL/glut.h> 
#include <vector>
#include "pvector.h"
#include "agent.h"
#include "point.h"
#include "graphics.h"
#include "flowField.h"
#include "path.h"

#define WIDTH       34
#define HEIGHT      34

#define WALL        30
#define DISTANCE    2

#define SEEK          1 //mouse follower
#define REFLECT       2 //apply force only near the wall
#define WIND          3 //wind force (no other force)
#define PATH_SIMPLE   4
#define PATH_COMPLEX  5

using namespace std;

int mode;

flowField flow;
graphics view;
vector<agent *> agents; //TODO: disqualify pointer
path pathMultiSegment;
path pathSimple;

int graphics::target_x = -WIDTH;
int graphics::target_y = HEIGHT;

//TODO: move to agent class
void reflect(agent &agent){    
    view.drawWall(WALL);
    int turnPoint = WALL - DISTANCE; 
    //TODO: refactor following code
    if(agent.position.x >= turnPoint){
       agent.desired = pvector( -agent.maxSpeed, agent.velocity.y );
       agent.steering = agent.desired - agent.velocity;
       agent.steering.limit(agent.maxForce);
       agent.force = agent.steering;
       agent.applyForce();
    }
    else if(agent.position.x <= -turnPoint){
       agent.desired = pvector( agent.maxSpeed, agent.velocity.y );
       agent.steering = agent.desired - agent.velocity;
       agent.steering.limit(agent.maxForce);
       agent.force = agent.steering;
       agent.applyForce();
    }
    else if(agent.position.y >= turnPoint){
       agent.desired = pvector( agent.velocity.x, -agent.maxSpeed );
       agent.steering = agent.desired - agent.velocity;
       agent.steering.limit(agent.maxForce);
       agent.force = agent.steering;
       agent.applyForce();
    }
    else if(agent.position.y <= -turnPoint){
       agent.desired = pvector( agent.velocity.x, agent.maxSpeed );
       agent.steering = agent.desired - agent.velocity;
       agent.steering.limit(agent.maxForce);
       agent.force = agent.steering;
       agent.applyForce();
    }
}

//TODO: move to agent class
void seek(agent &agent){
    agent.desired = agent.targetPoint - agent.position;
    agent.desired.normalize();
    agent.desired.mul(agent.maxSpeed);

    //arriving behavior
    if(agent.desired.magnitude() > agent.r) { agent.desired.limit(agent.maxSpeed); }
    else { agent.desired.limit(agent.maxSpeed / 2); }
    
    agent.steering = agent.desired - agent.velocity;
    agent.steering.limit(agent.maxForce);
    agent.force = agent.steering;
    agent.applyForce();
}

point getNormalPoint(point predicted, point start, point end){
   pvector a = predicted - start;
   pvector b = end - start;
   b.normalize();
   float a_dot_b = a.dotProduct(b);  
   b.mul(a_dot_b);   
   point normalPoint = start + b;
   return normalPoint;
}

void followMultiSegmentPath(agent &agent){   
   view.drawPath(pathMultiSegment.points.at(0), pathMultiSegment.points.at(1), pathMultiSegment.width);
   view.drawPath(pathMultiSegment.points.at(1), pathMultiSegment.points.at(2), pathMultiSegment.width);
   view.drawPath(pathMultiSegment.points.at(2), pathMultiSegment.points.at(3), pathMultiSegment.width);    

   float worldRecord = 1000000;
   point normalPoint;
   point predictedPos;
   pvector distance;

   for(auto it = pathMultiSegment.points.begin(); it < pathMultiSegment.points.end()-1; it++){
      point start = point((*it).x, (*it).y);
      point end   = point((*(it+1)).x, (*(it+1)).y);
      predictedPos = agent.position + agent.velocity; 
      normalPoint = getNormalPoint(predictedPos, start, end);
      
      if (normalPoint.x < start.x || normalPoint.x > end.x) {
         normalPoint = end;
      }      

      distance = predictedPos - normalPoint;
      if (distance.magnitude() < worldRecord) {
         worldRecord = distance.magnitude();
         agent.targetPoint = normalPoint;         
      }       
   }   
   seek(agent);
}

//TODO: move to agent class
void followPath(agent &agent){  
  point start = point(-WIDTH - 5,  HEIGHT - 40);
  point end   = point( WIDTH + 5, -HEIGHT + 40);
  pathSimple = path(6);
  pathSimple.addPoint(start);
  pathSimple.addPoint(end);
  view.drawPath(pathSimple.points.at(0), pathSimple.points.at(1), pathSimple.width);

  point predictedPos = agent.position + agent.velocity; 
  point normalPoint = getNormalPoint(predictedPos, start, end);
  pvector b = end - start;
  b.normalize();

  pvector distance  = predictedPos - normalPoint;
  agent.targetPoint = normalPoint  + b;
/*
  glBegin(GL_LINES);
  glVertex2f(predictedPos.x, predictedPos.y);
  glVertex2f(normalPoint.x, normalPoint.y);
  glEnd();  

  glPointSize(2.2);
  glBegin(GL_POINTS);
  glVertex2f(agent.targetPoint.x, agent.targetPoint.y);
  glEnd();*/
    
  if(distance.magnitude() > pathMultiSegment.width / 8){
     seek(agent);
  }  
}

//TODO: move to agent class
void wind(agent &agent){
    //pos_x, pos_y must be non negative integer
    int pos_x = abs((int)agent.position.x) % WIDTH;
    int pos_y = abs((int)agent.position.y) % HEIGHT;
    
    //TODO: modification required for non uniform fields
    agent.force = flow.getField(pos_x, pos_y); 
    agent.applyForce();
}

//TODO: move to graphics class
void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    
    glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
    glLoadIdentity(); //Reset the drawing perspective    
    glTranslatef(0.0f, 0.0f, -85.0f); //Move to the center of the triangle    
    
    for(auto it = agents.begin(); it < agents.end(); it++){ 
       switch(mode){//TODO: visitor pattern will be used later
           case SEEK:       
              (**it).targetPoint.x = graphics::target_x;
              (**it).targetPoint.y = graphics::target_y;
              seek(**it);       
           break;
           case REFLECT:     reflect(**it);    break; //velocity must be non zero                       
           case WIND:        wind(**it);       break;
           case PATH_SIMPLE: followPath(**it); break;
           case PATH_COMPLEX:followMultiSegmentPath(**it); break;
       }      
       (**it).updatePosition();         
       view.drawAgent((**it), (**it).velocity.getAngle()); 
    }      
    glutSwapBuffers();
}

int main(int argc, char** argv) {    
   cout << "SEEK:\t\t\t\t1" << endl << "REFLECT:\t\t\t2" << endl;
   cout << "WIND:\t\t\t\t3" << endl << "FOLLOW SIMPLE PATH:\t\t4" << endl;
   cout << "FOLLOW MULTISEGMENT PATH:\t5" << endl;;
   cin >> mode;

   view = graphics();    
   flow = flowField();
   
   pathMultiSegment = path(7);
   pathMultiSegment.addPoint(point(-40, 20));
   pathMultiSegment.addPoint(point(-14, 25));
   pathMultiSegment.addPoint(point( 10,  7));
   pathMultiSegment.addPoint(point( 40, 12));

   agent agent1 = agent(-30, 20.0);    
   agent agent2 = agent(-20.5, 20.0);
   agent agent3 = agent(-20.5, 8.0);
   agent agent4 = agent(-34.5, -16.0);

   agent1.setFeatures(0.5, 0.3, 0.1, 1);
   agent2.setFeatures(0.3, 0.4, 0.5, 1);
   agent3.setFeatures(0.2, 0.3, 0.1, 1);
   agent4.setFeatures(0.25,0.2, 0.5, 1); 
   
   agents.push_back(&agent1);
   agents.push_back(&agent2);
   agents.push_back(&agent3);   
   agents.push_back(&agent4);
  
   //TODO: move to graphics class
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(400, 400);   //TODO: magic number
   glutCreateWindow("Autonomous Steering Agents");
   glClearColor(0.7f, 0.9f, 1.0f, 1.0f); //set background color
   glEnable(GL_DEPTH_TEST);    
   glutDisplayFunc(drawScene);
   view.initGraphics();

   return 0;
}
