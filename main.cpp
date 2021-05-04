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
   
   cin >> mode;

   if(mode == STAY_IN_PATH)
      way.createPath_1();      
   else if(mode == STAY_IN_PATH_2)
      way.createPath_2();
}

void loop() {      
   view.refreshScene();   

   for(auto it = agent::agents.begin(); it < agent::agents.end(); it++){ 
      switch(mode){
         case FOLLOW_MOUSE:       
            (*it).targetPoint = view.getMousePosition();
            behavior.seek(*it, WITH_ARRIVING);
         break;

         case STAY_IN_FIELD:   
            view.drawWall(WALL);  
            behavior.stayInArea(*it, WALL - DISTANCE);
            behavior.separation(agent::agents, *it, 1);
         break;
         
         case IN_FLOW_FIELD:        
            flow = flowField(pvector(GRAVITY));
            behavior.inFlowField(*it, flow);
            flow = flowField(pvector(WIND_WEST));
            behavior.inFlowField(*it, flow);
         break;
         
         case STAY_IN_PATH: 
            view.drawPath(way);
            behavior.stayInPath(*it, way);
            behavior.separation(agent::agents, *it, 1);
         break;

         case STAY_IN_PATH_2:
            view.drawPath(way);
            behavior.stayInPath_2(*it, way);
         break;

         case FLOCK:            
            view.checkInScreen((*it));
            behavior.separation(agent::agents, *it, 0.9); //TODO: jitter must be eleminated
            behavior.align(agent::agents, *it, 1);
            behavior.cohesion(agent::agents, *it, 0.3);
         break;
         case WANDER:
            behavior.wander(*it);
         break;      
      }
   }

   for(auto it = agent::agents.begin(); it < agent::agents.end(); it++){       
      (*it).applyForce();
      (*it).updatePosition();         
      view.drawAgent(*it, (*it).vehicleColor);
   }

   graphics::timerEventFlag = false;
}

int main(int argc, char** argv) {    
   menu();

   view = graphics();       
   srand(time(NULL));
   color::createColors();
   agent::createAgents();     
   //agent::createRandomAgents(30);

   view.initGraphics(&argc, argv, loop);
   return 0;
}
