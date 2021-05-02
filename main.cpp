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
#include "steeringBehavior.h"
#include <stdlib.h>

#define WIDTH       34
#define HEIGHT      34

#define WALL        30
#define DISTANCE    2

#define MAX_NUMBER_OF_AGENTS 50

#define NUMBER_OF_AGENTS 17

using namespace std;

//TODO: create a client class and make all the globals below members of that class
int mode;
flowField flow;
graphics  view;
vector<agent> agents;
vector<color> colors;
path pathMultiSegment;
path pathSimple;
steeringBehavior behavior;

int graphics::target_x = -WIDTH;
int graphics::target_y = HEIGHT;

void createPath_1(){
   point start {-WIDTH - 5,  HEIGHT - 40}; 
   point end   { WIDTH + 5, -HEIGHT + 40};
   pathSimple  = path(6);
   pathSimple.addPoint(start);
   pathSimple.addPoint(end);   
}

void createRandomAgents(int agentCount){
   int size = MAX_NUMBER_OF_AGENTS * 2;
   int arr[size];   
   agent tempAgent {0, 0};
   srand(time(NULL));

   for(int i=0; i<size; i++){
      arr[i] = i;        
   }

   for (int i=0; i < size; i++){
      int r = rand() % size;
      swap(arr[i], arr[r]);
   }  

   for(int i=0; i < agentCount * 2; i=i+2){
      tempAgent.position.x = arr[i]   - WIDTH;
      tempAgent.position.y = arr[i+1] - HEIGHT;
      tempAgent.vehicleColor = colors.at( (i/2) % 8 );
      tempAgent.setFeatures(0.5, 0.3, 20, 1);
      agents.push_back(tempAgent);
   }
}

void createAgents(){
   agent agent1 {-10.0,  0.0};
   agent1.setFeatures(1.0, 0.7, 20, 1);
   agents.push_back(agent1);

   /*agent agent2 { 10.0,  0.0};
   agent agent3 {  0.0, 20.0};
   agent agent4 {  5.0,  5.0};      
   agent2.setFeatures(0.2, 0.3, 20, 1);
   agent3.setFeatures(0.3, 0.2, 20, 1);
   agent4.setFeatures(0.4, 0.1, 20, 1);   
   agents.push_back(agent2);
   agents.push_back(agent3);   
   agents.push_back(agent4);*/
}

void displayMenu(){
   cout << "Follow Mouse  : 1" << endl;
   cout << "Stay in Field : 2" << endl;
   cout << "In Flow Field : 3" << endl;
   cout << "Stay in Path  : 4" << endl;
   cout << "Stay in Path 2: 5" << endl;
   cout << "FLOCK         : 6" << endl;
   cout << "WANDER        : 7" << endl;
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

//TODO: move to graphics class
void drawScene() {      
   view.refreshScene();   
   for(auto it = agents.begin(); it < agents.end(); it++){ 
      switch(mode){
         case FOLLOW_MOUSE:       
            (*it).targetPoint = view.getMousePosition();
            behavior.seek(*it, WITH_ARRIVING);
         break;

         case STAY_IN_FIELD:   
            view.drawWall(WALL);  
            behavior.stayInArea(*it, WALL - DISTANCE);
            behavior.separation(agents, *it, 1);
         break;
         
         case IN_FLOW_FIELD:        
            flow = flowField(pvector(GRAVITY));
            behavior.inFlowField(*it, flow);
            flow = flowField(pvector(WIND_WEST));
            behavior.inFlowField(*it, flow);
         break;
         
         case STAY_IN_PATH: 
            view.drawPath(pathSimple);
            behavior.stayInPath(*it, pathSimple);
         break;

         case STAY_IN_PATH_2:
            view.drawPath(pathMultiSegment);
            behavior.stayInPath_2(*it, pathMultiSegment);
         break;

         case FLOCK:            
            view.checkInScreen((*it));
            behavior.separation(agents, *it, 0.9); //TODO: jitter must be eleminated
            behavior.align(agents, *it, 1);
            behavior.cohesion(agents, *it, 0.3);
         break;
         case WANDER:
            behavior.wander(agents);
         break;
         case PURSUIT:
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
      cout << endl;
   }
}

int main(int argc, char** argv) {    
   displayMenu();
   view = graphics();       
   
   createColors();
   createAgents();
   createPath_2();
   createPath_1();   
   //createRandomAgents(30);

   //TODO: move to graphics class
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(400, 400);   
   glutCreateWindow("Autonomous Steering Agents");
   glClearColor(0.7f, 0.7f, 0.7f, 1.0f); //set background color
   glEnable(GL_DEPTH_TEST);    
   glutDisplayFunc(drawScene);

   view.initGraphics();
   return 0;
}
