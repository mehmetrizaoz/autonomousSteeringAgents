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
#include "random.h"

using namespace std;

int mode;
flowField flow;
graphics  view;
path way;
steeringBehavior behavior;
string scenario;

void menu(){
   cout << "Follow Mouse  : 1" << endl;
   cout << "Stay in Field : 2" << endl;
   cout << "In Flow Field : 3" << endl;
   cout << "Stay in Path  : 4" << endl;
   cout << "Stay in Path 2: 5" << endl;
   cout << "FLOCK         : 6" << endl;
   cout << "WANDER        : 7" << endl;
   cout << "FLEE          : 8" << endl;
   
   cin >> mode;
}

void displayMode(){
   glColor3f (0.0, 0.0, 1.0);
   glRasterPos2f(-34, 32.5);
   for ( string::iterator it=scenario.begin(); it!=scenario.end(); ++it){ 
      glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *it);
   }   
}

void loop() {      
   view.refreshScene();   
   for(auto it = agent::agents.begin(); it < agent::agents.end(); it++){
      if(mode==FLOCK){
         view.checkInScreen((*it));
         pvector sep  = behavior.separation(agent::agents, *it);
         sep.mul(1.5);/*
         point a = point(sep.x, sep.y);
         a.mul(10);
         view.drawLine( (*it).position, 
                        (*it).position + a,
                        color(1,0,0)
                     );*/
         

         pvector ali = behavior.align(agent::agents, *it);
         ali.mul(4);/*
         a = point(ali.x, ali.y);
         a.mul(10);
         view.drawLine( (*it).position, 
                        (*it).position + a,
                        color(0,1,0)
                     );*/
         
         pvector coh = behavior.cohesion(agent::agents, *it);
         coh.mul(0.1);/*
         a = point(coh.x, coh.y);
         a.mul(10);
         view.drawLine( (*it).position, 
                        (*it).position + a,
                        color(0,0,1)
                     );*/

         (*it).force = sep + ali + coh;
         (*it).desiredVelocity = (*it).force + (*it).velocity;
         (*it).targetPoint = (*it).position + (*it).desiredVelocity;
         (*it).arrive = true;
      } 

      else if (mode == FOLLOW_MOUSE){
         (*it).targetPoint = view.getMousePosition();
         (*it).force = behavior.seek(*it);
         (*it).arrive = true;
      }

      else if (mode == STAY_IN_FIELD){ //TODO: apply force to agent if it is out of the field
         view.drawWall(WALL);  
         (*it).force  = behavior.stayInArea(*it, WALL - DISTANCE);
         (*it).force += behavior.separation(agent::agents, *it);         
      }         
      
      else if(mode == IN_FLOW_FIELD){
         flow = flowField(pvector(GRAVITY));
         (*it).force  = behavior.inFlowField(*it, flow);
         
         flow = flowField(pvector(WIND_WEST));
         (*it).force += behavior.inFlowField(*it, flow);
      }
         
      else if(mode == STAY_IN_PATH){
         view.drawPath(way);
         (*it).force  = behavior.stayInPath(*it, way);
         (*it).force += behavior.separation(agent::agents, *it);
      }

      else if(mode == STAY_IN_PATH_2){ //TODO: jitter exist
         view.drawPath(way);
         pvector seek = behavior.stayInPath_2(*it, way, view);
         /*point a = point(seek.x, seek.y);
         a.mul(10);
         view.drawLine( (*it).position, 
                        (*it).position + a,
                        color(1,0,0)
                     );*/

         pvector sep  = behavior.separation(agent::agents, *it);
         sep.mul(5);
         /*a = point(sep.x, sep.y);
         a.mul(10);
         view.drawLine( (*it).position, 
                        (*it).position + a,
                        color(0,0,1));*/                     
         
         (*it).force = sep + seek;
         //(*it).desiredVelocity = (*it).force + (*it).velocity;
         //(*it).targetPoint = (*it).position + (*it).desiredVelocity;
         //(*it).arrive = true;
      }

      else if(mode == WANDER){
         //TODO: logic must be improved
         (*it).force = behavior.wander(*it);
      }  

      else if(mode == FLEE){
         (*it).force = behavior.flee((*it), view);
      }
   }

   for(auto it = agent::agents.begin(); it < agent::agents.end(); it++){       
      (*it).updatePosition(mode, (*it).arrive);         
      view.drawAgent(*it, (*it).vehicleColor);
   }

   displayMode();
}

void init(int * argv, char** argc, void (*callback)()){         
   srand(time(NULL));
   color::createColors();
   //agent::createAgents();  

   if(mode == STAY_IN_PATH){
      way.createPath_1();   
      agent::createRandomAgents(30, 0.6, 0.3);
      scenario = "STAY_IN_PATH";
   }   
   else if(mode == STAY_IN_PATH_2){
      way.createPath_2();
      agent::createRandomAgents(40, 0.4, 0.2);
      scenario = "STAY_IN_PATH_2";
   }
   else if(mode == FLEE){
      agent::createTroop(196); 
      scenario = "FLEE";  
   }
   else if(mode == STAY_IN_FIELD){
      agent::createRandomAgents(30, 0.5, 0.5);
      scenario = "STAY_IN_FIELD";
   }
   else if(mode == FOLLOW_MOUSE){
      agent::createRandomAgents(30, 0.6, 0.3);
      scenario = "FOLLOW_MOUSE";
   }
   else if(mode == FLOCK){
      agent::createRandomAgents(50, 1, 0.3);
      scenario = "FLOCK";
   }   
   else if(mode == WANDER){
      agent::createRandomAgents(30, 0.6, 0.3);
      scenario = "WANDER";
   }  
   else if(mode == IN_FLOW_FIELD){
      agent::createRandomAgents(30, 0.6, 0.3);
      scenario = "IN_FLOW_FIELD";
   }       

   view = graphics(); 
   view.initGraphics(argv, argc, loop);
}

int main(int argc, char** argv) {    
   menu();  
   init(&argc, argv, loop);
   return 0;
}
