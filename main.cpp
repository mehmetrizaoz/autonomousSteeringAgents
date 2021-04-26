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

#define NUMBER_OF_AGENTS 17

using namespace std;

int mode; //TODO: move to agent class, make it static variable
flowField flow;
graphics  view;
vector<agent> agents;
vector<color> colors;
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
            (*it).addTargetSeekForce();
            /*cout << "force :" << (*it).force.x << " " << (*it).force.y << endl;

            flow = flowField(pvector(WIND_WEST));
            (*it).addFlowForce(flow);
            cout << "force :" << (*it).force.x << " " << (*it).force.y << endl;
            cout << endl;  */          
         break;

         case REFLECT:     
            (*it).addReflectionForce(view, WALL, DISTANCE);
            (*it).addSeparationForce(agents);            
         break;
         
         case FLOW_FIELD:        
            flow = flowField(pvector(GRAVITY));
            (*it).addFlowForce(flow);

            flow = flowField(pvector(WIND_WEST));
            (*it).addFlowForce(flow);            
         break;
         
         case PATH_SIMPLE: 
            (*it).followSimplePath(view, pathSimple);             
         break;

         case PATH_COMPLEX:
            (*it).followMultiSegmentPath(view, pathMultiSegment);
         break;

         case FLOCK:
            view.checkInScreen((*it));
            (*it).addSeparationForce(agents);                    
            //(*it).addAlignForce(agents);
            //(*it).addCohesionForce(agents);
         break;

         default:
         break;
      }
      (*it).applyForce();
      (*it).updatePosition();         
      view.drawAgent(*it, (*it).vehicleColor);
   }      
   glutSwapBuffers();
}

void createRandomAgents(int number){
   int size = number * 4;
   int arr[size];
   int dividor = WIDTH;
   float offset = 10;
   agent tempAgent = agent(0, 0);

   for(int i=0; i<size; i++)
      arr[i] = i;  
   
   srand(time(NULL));
   for (int i=0; i<size ;i++){
      int r = i + (rand() % (size -i));
      swap(arr[i], arr[r]);
   }
   
   for(int i=0; i<size; i=i+4){
      tempAgent.position.x = arr[i]   - WIDTH;
      tempAgent.position.y = arr[i+1] - HEIGHT;
      tempAgent.vehicleColor = colors.at( (i/4) %8 );
      tempAgent.setMass(1);
      tempAgent.setR(3);
      if(arr[i+2] < offset || arr[i+2] > 45)
         arr[i+2] = offset;
      if(arr[i+3] < offset || arr[i+3] > 45)
         arr[i+3] = offset; 
      tempAgent.setMaxForce( float(arr[i+2]) / dividor );
      tempAgent.setMaxSpeed( float(arr[i+3]) / dividor );
      agents.push_back(tempAgent);
   }
}

void createAgents(){
   agent agent1 = agent(-10.0,  0.0);    
   agent agent2 = agent( 10.0,  0.0);
   //agent agent3 = agent(-20.5,   8.0);
   //agent agent4 = agent(-34.5, -16.0);
   
   /*agent1.setFeatures(0.3, 0.5, 3, 1);
   agent2.setFeatures(0.3, 0.5, 2, 1);
   agent3.setFeatures(0.2, 0.1, 1, 1); // ****
   agent4.setFeatures(0.25,0.2, 3, 1);*/
   agent1.setFeatures(0.3, 0.3, 3, 1);
   agent2.setFeatures(0.3, 0.3, 3, 1);

   agent1.velocity.x =  0.1;
   agent2.velocity.x = -0.1;
   
   agents.push_back(agent1);
   agents.push_back(agent2);
   //agents.push_back(agent3);   
   //agents.push_back(agent4);
}

void displayMenu(){
   cout << "SEEK: 1" << endl;
   cout << "REFLECTION: 2" << endl;
   cout << "FLOW_FIELD: 3" << endl;
   cout << "SIMPLE PATH: 4" << endl;
   cout << "MULTISEGMENT PATH: 5" << endl;
   cout << "FLOCK: 6" << endl;
   cin >> mode;
}

void createMultisegmentPath(){
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
   createAgents();
   createMultisegmentPath();
   createSimplePath();   
   //createRandomAgents(10);

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
