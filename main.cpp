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
path myPath;
steeringBehavior behavior;
string scenario;
vector<obstacle> obstacles;
color myColor;
vector<agent> agents;

void createPath_1(path &p){
   point start = point(-WIDTH-5,  HEIGHT-40);
   point end   = point( WIDTH+5, -HEIGHT+40);
   p.addPoint(start);
   p.addPoint(end);      
}

void createPath_2(path &p){
   p.addPoint(point(-40,  5));
   p.addPoint(point(-14, 15));
   p.addPoint(point( 10,  7));
   p.addPoint(point( 40, 12));
}


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

void createRandomAgents(int agentCount, const float mForce, const float mSpeed){
   int size = MAX_NUMBER_OF_AGENTS * 2;   
   int arr[size];
   random::createRandomArray(arr, size);
   agent tempAgent {0, 0};
   for(int i=0; i < agentCount * 2; i=i+2){
      tempAgent.position.x = arr[i]   - WIDTH;
      tempAgent.position.y = arr[i+1] - HEIGHT;
      tempAgent.fillColor = myColor.colors.at( (i/2) % 8 );
      tempAgent.setFeatures(mForce, mSpeed, 5, 1); 
      agents.push_back(tempAgent);
   }
}

void createAgents(){
    agent agent1 {-10.0,  0.0};
    agent1.id = 1;
    agent1.name = "gazelle";    
    agent1.fillColor = myColor.getColor(BLUE);
    agent1.setFeatures(0.5, 0.2, 5, 1);
    agents.push_back(agent1);

    agent agent2 { 10.0,  0.0};
    agent2.id = 2;
    agent2.name = "lion";
    agent2.fillColor = myColor.getColor(YELLOW);
    agent2.setFeatures(0.4, 0.2, 5, 1);    
    agents.push_back(agent2);
}

void createTroop(int agentCount){
    //TODO: magic numbers
    agent tempAgent {0, 0};
    pvector location {-33, 33};
   
    for(int i=0; i < agentCount; i++){
        tempAgent.id = i;
        tempAgent.velocity = pvector(0, 0);
        tempAgent.position.x = location.x;
        tempAgent.position.y = location.y;
        tempAgent.targetPoint = tempAgent.position;                 

        if( ((i+1) % 14) == 0){
           location.y -= 5;
           location.x  = -33;
        }
        else
           location.x += 5; 

        tempAgent.fillColor = myColor.colors.at( (i/2) % 8 );
        tempAgent.setFeatures(0.3, 0.3, 5, 1);
        agents.push_back(tempAgent);
    }
}

void loop() {      
   view.refreshScene();   
   //TODO: create scenario abstract class and inherit all scenarios from it, remove code below
   for(auto it = agents.begin(); it < agents.end(); it++){
      if(mode==FLOCK){
         view.forceInScreen((*it));
         
         pvector sep = behavior.separation(agents, *it);
         sep.mul(1.5);         
         pvector ali = behavior.align(agents, *it);
         ali.mul(4);    
         pvector coh = behavior.cohesion(agents, *it);
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
         view.drawWall(WALL, myColor);  
         (*it).force  = behavior.stayInArea(*it, WALL - DISTANCE);
         (*it).force += behavior.separation(agents, *it);         
      }         
      
      else if(mode == IN_FLOW_FIELD){
         flow = flowField(pvector(GRAVITY));
         (*it).force  = behavior.inFlowField(*it, flow);
         
         flow = flowField(pvector(WIND_WEST));
         (*it).force += behavior.inFlowField(*it, flow);
      }
         
      else if(mode == STAY_IN_PATH){         
         view.drawPath(myPath, myColor);
         (*it).force  = behavior.stayInPath(*it, myPath);
         (*it).force += behavior.separation(agents, *it);
      }

      else if(mode == STAY_IN_PATH_2){ 
         view.drawPath(myPath, myColor);
         pvector seek = behavior.stayInPath_2(*it, myPath, view);
         pvector sep  = behavior.separation(agents, *it);
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
         if((*it).name == "gazelle"){
            (*it).targetPoint = view.getMousePosition();
            (*it).force  = behavior.seek(*it);            
         }
         else{//lion
            (*it).force  = behavior.pursuit(agents, *it, view);            
         }
         (*it).arrive = true;
      }
      
      else if(mode == EVADE){
         if((*it).name == "lion"){
            (*it).targetPoint = view.getMousePosition();
            (*it).force  = behavior.seek(*it);
            (*it).arrive = true;
         }
         else{//gazelle
            (*it).force  = behavior.evade(agents, *it, view);
         }
      }      

      else if(mode == AVOID_OBSTACLE){
         for(auto it = obstacles.begin(); it < obstacles.end(); it++){
            point p = (*it).p;
            view.drawCircle(p, (*it).r);
         }

         (*it).targetPoint = view.getMousePosition();
         pvector seek  = behavior.seek(*it);
         seek.mul(0.5);

         pvector avoid = behavior.avoid(obstacles, *it);
         (*it).force = avoid + seek;   
         (*it).arrive = true;
      }
   }

   for(auto it = agents.begin(); it < agents.end(); it++){       
      (*it).updatePosition(mode, (*it).arrive);        
      view.drawAgent(*it, (*it).fillColor);
   }
      
   view.drawText(scenario, point(-34, 32.25)); //TODO: magic numbers, define left corner
}

void createObstacle(vector<obstacle> &obstacles){   
   obstacles.push_back(obstacle(point(0,0), 8));   
   obstacles.push_back(obstacle(point(-20,0), 3));  
   obstacles.push_back(obstacle(point(20,-10), 4));
}

void init(int * argv, char** argc, void (*callback)()){         
   srand(time(NULL));
   myColor.createColors();

   if(mode == STAY_IN_PATH){
      myPath = path(6);
      createPath_1(myPath);   
      createRandomAgents(30, 0.6, 0.3);
      scenario = "STAY IN PATH";
   }
   else if(mode == STAY_IN_PATH_2){
      myPath = path(8);
      createPath_2(myPath);
      createRandomAgents(40, 0.4, 0.2);
      scenario = "STAY IN PATH 2";
   }
   else if(mode == FLEE){
      createTroop(196); 
      scenario = "FLEE";  
   }
   else if(mode == STAY_IN_FIELD){
      createRandomAgents(30, 0.5, 0.5);
      scenario = "STAY IN FIELD";
   }
   else if(mode == FOLLOW_MOUSE){
      createRandomAgents(30, 0.6, 0.3);
      scenario = "FOLLOW MOUSE";
   }
   else if(mode == FLOCK){
      createRandomAgents(50, 1.0, 0.3);
      scenario = "FLOCK";
   }
   else if(mode == WANDER){
      createRandomAgents(30, 0.6, 0.3);
      scenario = "WANDER";
   }
   else if(mode == IN_FLOW_FIELD){
      createRandomAgents(30, 0.6, 0.3);
      scenario = "IN FLOW FIELD";
   }
   else if(mode == PURSUIT){      
      createAgents();
      scenario = "PURSUIT";
   }
   else if(mode == EVADE){      
      createAgents();
      scenario = "EVADE";
   }
   else if(mode == AVOID_OBSTACLE){
      createAgents();
      createObstacle(obstacles);
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


