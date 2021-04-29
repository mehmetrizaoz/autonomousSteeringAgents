#include <iostream>
#include <GL/glut.h> 
#include <vector>
#include "pvector.h"
#include "agent.h"
#include "point.h"
#include "color.h"
#include "graphics.h"
#include "flowField.h"
#include "path.h"
#include <stdlib.h>

#define WIDTH       34
#define HEIGHT      34

#define WALL        30
#define DISTANCE    2

#define MAX_NUMBER_OF_AGENTS 34

#define NUMBER_OF_AGENTS 17

using namespace std;

//TODO: too many global variables
int mode;
flowField flow;
graphics  view;
vector<agent> agents;
vector<color> colors;
path pathMultiSegment;
path pathSimple;

int graphics::target_x = -WIDTH;
int graphics::target_y = HEIGHT;

void createPath_1(){
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
            (*it).targetPoint = view.getMousePosition();
            (*it).seek(WITH_ARRIVING);      
         break;

         case REFLECT:     
            (*it).reflect(view, WALL, DISTANCE);
            (*it).separation(agents, 1);            
         break;
         
         case FLOW_FIELD:        
            flow = flowField(pvector(GRAVITY));
            (*it).uniformFlow(flow);

            flow = flowField(pvector(WIND_WEST));
            (*it).uniformFlow(flow);            
         break;
         
         case PATH_SIMPLE: 
            (*it).simplePath(view, pathSimple);             
         break;

         case PATH_COMPLEX:
            (*it).curvedPath(view, pathMultiSegment);
         break;

         case FLOCK:
            view.checkInScreen((*it));
            (*it).separation(agents, 1);                    
            (*it).align(agents, 1);
            (*it).cohesion(agents, 0.4);
            //TODO: print all vectors and check if sum is correct
         break;

         case FOLLOW_LEAD:
         break;

         case HIDE:
         break;

         case PATH_LOOP:
         break;
      }
   }

   for(auto it = agents.begin(); it < agents.end(); it++){ 
      (*it).applyForce();
      (*it).updatePosition();         
      view.drawAgent(*it, (*it).vehicleColor);
   }   
   glutSwapBuffers();
}

void createRandomAgents(int agentCount){
   int arr[MAX_NUMBER_OF_AGENTS];   
   agent tempAgent = agent(0, 0);
   srand(time(NULL));

   for(int i=0; i<MAX_NUMBER_OF_AGENTS; i++){
      arr[i] = i;        
   }

   for (int i=0; i < MAX_NUMBER_OF_AGENTS ;i++){
      int r = rand() % MAX_NUMBER_OF_AGENTS;
      swap(arr[i], arr[r]);
   }  

   for(int i=0; i < agentCount * 2; i=i+2){
      tempAgent.position.x = arr[i]   - WIDTH;
      tempAgent.position.y = arr[i+1] - HEIGHT;
      tempAgent.vehicleColor = colors.at( (i/2) % 8 );
      tempAgent.setFeatures(0.9, 0.3, 20, 1);
      agents.push_back(tempAgent);
   }
}

void createAgents(){
   agent agent1 = agent(-10.0,  0.0);    
   agent agent2 = agent( 10.0,  0.0);
   agent agent3 = agent(  0.0, 20.0);
   agent agent4 = agent(  5.0,  5.0);
   
   agent1.setFeatures(0.5, 0.4, 20, 1);
   agent2.setFeatures(0.2, 0.3, 20, 1);
   agent3.setFeatures(0.3, 0.2, 20, 1);
   agent4.setFeatures(0.4, 0.1, 20, 1);

   agents.push_back(agent1);
   agents.push_back(agent2);
   agents.push_back(agent3);   
   agents.push_back(agent4);
}

void displayMenu(){
   cout << "SEEK:   1" << endl;
   cout << "REFLECT:2" << endl;
   cout << "FLOW:   3" << endl;
   cout << "PATH 1: 4" << endl;
   cout << "PATH 2: 5" << endl;
   cout << "FLOCK:  6" << endl;
   cin >> mode;
}

void createPath_2(){
   pathMultiSegment = path(7);
   pathMultiSegment.addPoint(point(-40,  5));
   pathMultiSegment.addPoint(point(-14, 15));
   pathMultiSegment.addPoint(point( 10,  7));
   pathMultiSegment.addPoint(point( 40, 12));
}

void createColors(){
   colors.push_back(color(0.0, 0.0, 0.0));
   colors.push_back(color(0.0, 0.0, 1.0));
   colors.push_back(color(0.0, 1.0, 0.0));
   colors.push_back(color(0.0, 1.0, 1.0));
   colors.push_back(color(1.0, 0.0, 0.0));
   colors.push_back(color(1.0, 0.0, 1.0));
   colors.push_back(color(1.0, 1.0, 0.0));
   colors.push_back(color(1.0, 1.0, 1.0));
}

int main(int argc, char** argv) {    
   displayMenu();
   view = graphics();       
   
   createColors();
   //createAgents();
   createPath_2();
   createPath_1();   
   createRandomAgents(30);

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
