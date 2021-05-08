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

   if(mode == STAY_IN_PATH)
      way.createPath_1();      
   else if(mode == STAY_IN_PATH_2)
      way.createPath_2();
}

void loop() {      
   view.refreshScene();   

   for(auto it = agent::agents.begin(); it < agent::agents.end(); it++){
      if(mode==FLOCK){
         //TODO: jitter exist
         view.checkInScreen((*it));
         pvector sep  = behavior.separation(agent::agents, *it); //TODO: jitter must be eleminated
         sep.mul(1.5);

         pvector ali = behavior.align(agent::agents, *it);
         ali.mul(1.0);

         pvector coh = behavior.cohesion(agent::agents, *it);
         coh.mul(0.1);

         (*it).force = sep + ali + coh;
      } 

      else if (mode == FOLLOW_MOUSE){
         (*it).targetPoint = view.getMousePosition();
         (*it).force = behavior.seek(*it);
         (*it).arrive = true;
      }

      else if (mode == STAY_IN_FIELD){
         view.drawWall(WALL);  
         (*it).force  = behavior.stayInArea(*it, WALL - DISTANCE);
         (*it).force += behavior.separation(agent::agents, *it);         
      }         
      
      else if(mode ==IN_FLOW_FIELD){
         flow = flowField(pvector(GRAVITY));
         (*it).force  = behavior.inFlowField(*it, flow);
         
         flow = flowField(pvector(WIND_WEST));
         (*it).force += behavior.inFlowField(*it, flow);
      }
         
      else if(mode ==STAY_IN_PATH){
         view.drawPath(way);
         (*it).force  = behavior.stayInPath(*it, way);
      }

      else if(mode == STAY_IN_PATH_2){
         //TODO: jitter exist
         view.drawPath(way);
         pvector seek = behavior.stayInPath_2(*it, way);
         seek.mul(0.5);
         (*it).force = seek;
      }

      else if(mode == WANDER){
         //TODO: jitter exist
         (*it).force = behavior.wander(*it);
      }  

      else if(mode == FLEE){     
         //TODO: bug exist for agents at the corners                  
         pvector dist = (*it).targetPoint - view.getMousePosition();
         view.drawPoint((*it).targetPoint);
         if(dist.magnitude() < 15){  
            (*it).arrive = false;
            (*it).desiredVelocity = (*it).position - view.getMousePosition();
            (*it).steering = (*it).desiredVelocity - (*it).velocity;      
            (*it).force = (*it).steering;
            if((*it).id == 0){
               cout << "id " << (*it).id;
               view.getMousePosition().print("mouse");
               (*it).targetPoint.print("target");
               cout << "dist " <<  dist.magnitude() << endl;
               (*it).steering.print("steer");
               (*it).position.print("pos");
               (*it).desiredVelocity.print("desired");               
            }
         }
         else{
            (*it).arrive = true;
            (*it).desiredVelocity = (*it).targetPoint - (*it).position;
            (*it).steering = (*it).desiredVelocity - (*it).velocity;
            (*it).force = (*it).steering;
         }
      }
   }

   for(auto it = agent::agents.begin(); it < agent::agents.end(); it++){       
      (*it).updatePosition(mode, (*it).arrive);         
      view.drawAgent(*it, (*it).vehicleColor);
   }
}

int main(int argc, char** argv) {    
   menu();
   view = graphics();       
   srand(time(NULL));
   color::createColors();

   //agent::createAgents();  
   //agent::createAgentsInLine(196);
   agent::createRandomAgents(30);

   view.initGraphics(&argc, argv, loop);
   return 0;
}
