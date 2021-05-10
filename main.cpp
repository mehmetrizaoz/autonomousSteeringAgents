#include <iostream>
#include <GL/glut.h> 
#include <vector>
#include "pvector.h"
#include "agent.h"
#include "point.h"
#include "color.h"
#include "graphics.h"
#include "flowField.h"
#include "obstacle.h"
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
   cout << "Follow Mouse       : 1" << endl;
   cout << "Stay in Field      : 2" << endl;
   cout << "In Flow Field      : 3" << endl;
   cout << "Stay in Path       : 4" << endl;
   cout << "Stay in Path 2     : 5" << endl;
   cout << "FLOCK              : 6" << endl;
   cout << "WANDER             : 7" << endl;
   cout << "FLEE               : 8" << endl;
   cout << "PURSUIT            : 9" << endl;
   cout << "EVADE              : 10" << endl;
   cout << "OBSTACLE AVOIDANCE : 11" << endl;
   cin >> mode;
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
         ali.mul(4);    
         pvector coh = behavior.cohesion(agent::agents, *it);
         coh.mul(0.1);

         (*it).force = sep + ali + coh;
         (*it).desiredVelocity = (*it).force + (*it).velocity;
         (*it).targetPoint = (*it).position + (*it).desiredVelocity;
         (*it).arrive = true;
      } 
      
      else if (mode == FOLLOW_MOUSE){
         (*it).targetPoint = view.getMousePosition();
         (*it).force  = behavior.seek(*it);
         (*it).arrive = true;
      }

      else if (mode == STAY_IN_FIELD){
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

      else if(mode == STAY_IN_PATH_2){ 
         view.drawPath(way);
         pvector seek = behavior.stayInPath_2(*it, way, view);
         pvector sep  = behavior.separation(agent::agents, *it);
         sep.mul(5);         
         (*it).force = sep + seek;
      }

      else if(mode == WANDER){//TODO: logic must be improved        
         (*it).force = behavior.wander(*it);
      }  

      else if(mode == FLEE){
         (*it).force = behavior.flee((*it), view, view.getMousePosition());
      }

      else if(mode == PURSUIT){
         if( (*it).name == "gazelle" ){
            (*it).targetPoint = view.getMousePosition();
            (*it).force  = behavior.seek(*it);
            (*it).arrive = true;
         }
         else{ //lion
            (*it).force  = behavior.pursuit(agent::agents, *it);
            (*it).arrive = true;
         }
      }
      
      else if(mode == EVADE){
         if( (*it).name == "lion" ){
            (*it).targetPoint = view.getMousePosition();
            (*it).force  = behavior.seek(*it);
            (*it).arrive = true;
         }
         else{//gazelle
            (*it).force  = behavior.evade(agent::agents, *it, view);
         }
      }      

      else if(mode == AVOID_OBSTACLE){         
         obstacle::draw();
         (*it).targetPoint = view.getMousePosition();
         pvector seek  = behavior.seek(*it);
         seek.mul(0.5);
         (*it).force = seek;     

         point a = point(seek.x, seek.y);
         view.drawLine( (*it).position, 
                        (*it).position + a,
                        color(1,0,0));   

         pvector vel = (*it).velocity;
         vel.normalize();
         vel.mul(1); //max_see_ahead
         pvector ahead  = vel + (*it).position;
         pvector ahead2 = ahead;
         
         float dist  = (ahead  - obstacle::obstacles.at(0).p).magnitude();
         float dist2 = (ahead2 - obstacle::obstacles.at(0).p).magnitude();
         
         if(dist < obstacle::obstacles.at(0).r || dist2 < obstacle::obstacles.at(0).r){
            pvector avoidance = ahead - obstacle::obstacles.at(0).p;
            avoidance.normalize();
            avoidance.mul(20);
            
            a = point(avoidance.x, avoidance.y);
            view.drawLine( (*it).position, 
                        (*it).position + a,
                        color(0,1,0));              
            (*it).force += avoidance;
         }
         
         (*it).arrive = true;
      }

   }

   for(auto it = agent::agents.begin(); it < agent::agents.end(); it++){       
      (*it).updatePosition(mode, (*it).arrive);        
      view.drawAgent(*it, (*it).vehicleColor);
   }

   view.drawText(scenario);
}

void init(int * argv, char** argc, void (*callback)()){         
   srand(time(NULL));
   color::createColors();

   if(mode == STAY_IN_PATH){
      way.createPath_1();   
      agent::createRandomAgents(30, 0.6, 0.3);
      scenario = "STAY IN PATH";
   }
   else if(mode == STAY_IN_PATH_2){
      way.createPath_2();
      agent::createRandomAgents(40, 0.4, 0.2);
      scenario = "STAY IN PATH 2";
   }
   else if(mode == FLEE){
      agent::createTroop(196); 
      scenario = "FLEE";  
   }
   else if(mode == STAY_IN_FIELD){
      agent::createRandomAgents(30, 0.5, 0.5);
      scenario = "STAY IN FIELD";
   }
   else if(mode == FOLLOW_MOUSE){
      agent::createRandomAgents(30, 0.6, 0.3);
      scenario = "FOLLOW MOUSE";
   }
   else if(mode == FLOCK){
      agent::createRandomAgents(50, 1.0, 0.3);
      scenario = "FLOCK";
   }
   else if(mode == WANDER){
      agent::createRandomAgents(30, 0.6, 0.3);
      scenario = "WANDER";
   }
   else if(mode == IN_FLOW_FIELD){
      agent::createRandomAgents(30, 0.6, 0.3);
      scenario = "IN FLOW FIELD";
   }
   else if(mode == PURSUIT){      
      agent::createAgents();
      scenario = "PURSUIT";
   }
   else if(mode == EVADE){      
      agent::createAgents();
      scenario = "EVADE";
   }
   else if(mode == AVOID_OBSTACLE){
      agent::createAgents();
      obstacle::createObstacle();
      scenario = "OBSTACLE AVOIDANCE";
   }

   view = graphics(); 
   view.initGraphics(argv, argc, loop);
}

int main(int argc, char** argv) {    
   menu();  
   init(&argc, argv, loop);
   return 0;
}
