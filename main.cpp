#include <iostream>
#include <GL/glut.h> 
#include <vector>
#include "pvector.h"
#include "agent.h"
#include "point.h"
#include "graphics.h"
#include "flowField.h"
#include "path.h"
#include <stdlib.h>

#define WIDTH       34
#define HEIGHT      34

#define WALL        30
#define DISTANCE    2

using namespace std;

int mode; //TODO: move to agent class, make it static variable
flowField flow;
graphics  view;
vector<agent> agents;
path pathMultiSegment;
path pathSimple;

int graphics::target_x = -WIDTH;
int graphics::target_y = HEIGHT;

void createSimplePath(){
  point start = point(-WIDTH - 5,  HEIGHT - 40);
  point end   = point( WIDTH + 5, -HEIGHT + 40);
  pathSimple  = path(6);
  pathSimple.addPoint(start);
  pathSimple.addPoint(end);   
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
            (*it).targetPoint.x = graphics::target_x;
            (*it).targetPoint.y = graphics::target_y;
            (*it).seekTarget();              
         break;

         case REFLECT:     
            (*it).reflect(view, WALL, DISTANCE);    
         break;
         
         case WIND:        
            (*it).applyWindForce(flow);  
         break;
         
         case PATH_SIMPLE: 
            (*it).followSimplePath(view, pathSimple);
         break;

         case PATH_COMPLEX:
            (*it).followMultiSegmentPath(view, pathMultiSegment);
         break;

         default:
         break;
      }      
      (*it).updatePosition();         
      view.drawAgent(*it);
   }      
   glutSwapBuffers();
}

void createRandomAgents(){
   int a[68];
   for(int i=0; i<68; i++){
      a[i] = i;
   }
   
   srand(time(NULL));
   for (int i=0; i<68 ;i++){
      int r = i + (rand() % (68 -i));
      swap(a[i], a[r]);
   }
   
   /*
   for(int i=0; i<68; i++){
      cout << float(a[i]) / 34 << " ";
      if(i%10 == 0)
         cout << endl;
   }*/
   
   agent tempAgent = agent(0, 0);
   for(int i=0; i<68; i=i+4){
      cout << a[i] << " " << a[i+1] << endl;
      tempAgent.position.x = a[i]   - 34;
      tempAgent.position.y = a[i+1] - 34;
      tempAgent.setMass(1);
      tempAgent.setR(3);
      tempAgent.setMaxForce( float(a[i+2]) / 34 - 0.02);
      tempAgent.setMaxSpeed( float(a[i+3]) / 34 + 0.01);
      agents.push_back(tempAgent);
   }
}

void createAgents(){
   agent agent1 = agent(-30.0,  20.0);    
   agent agent2 = agent(-20.5,  20.0);
   agent agent3 = agent(-20.5,   8.0);
   agent agent4 = agent(-34.5, -16.0);

   agent1.setFeatures(0.5, 0.3, 0.1, 1);
   agent2.setFeatures(0.3, 0.4, 0.5, 1);
   agent3.setFeatures(0.2, 0.3, 0.1, 1);
   agent4.setFeatures(0.25,0.2, 0.5, 1); 
   
   agents.push_back(agent1);
   agents.push_back(agent2);
   agents.push_back(agent3);   
   agents.push_back(agent4);
}

void displayMenu(){
   cout << "SEEK\t\t\t\t:1" << endl << "REFLECT\t\t\t\t:2" << endl;
   cout << "WIND\t\t\t\t:3" << endl << "FOLLOW SIMPLE PATH\t\t:4" << endl;
   cout << "FOLLOW MULTISEGMENT PATH\t:5" << endl;
   cout << "GROUP BEHAVIOR\t\t\t:6" << endl;
   cin >> mode;
}

void createMultisegmentPath(){
   pathMultiSegment = path(7);
   pathMultiSegment.addPoint(point(-40, 20));
   pathMultiSegment.addPoint(point(-14, 25));
   pathMultiSegment.addPoint(point( 10,  7));
   pathMultiSegment.addPoint(point( 40, 12));
}

int main(int argc, char** argv) {    
   displayMenu();

   view = graphics();    
   flow = flowField();
   
   //createAgents();
   createMultisegmentPath();
   createSimplePath();
   
   createRandomAgents();

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
