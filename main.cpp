#include <iostream>
#include <GL/glut.h> 
#include <vector>
#include "pvector.h"
#include "agent.h"
#include "point.h"
#include "color.h"
#include "graphics.h"
#include "obstacle.h"
#include "path.h"
#include "steeringBehavior.h"
#include <stdlib.h>
#include "random.h"

#include "mouseFollower.h"
#include "prison.h"
#include "windy.h"
#include "wander.h"
#include "pursuit.h"
#include "flee.h"
#include "evade.h"
#include "flock.h"
#include "pathFollower.h"

using namespace std;

int mode;
graphics  view;
steeringBehavior behavior;
string scenario;
vector<obstacle> obstacles;
color myColor;
vector<agent> agents;


void menu(){
   cout << "Follow Mouse       : 1" << endl;
   cout << "Stay in Field      : 2" << endl;
   cout << "In Flow Field      : 3" << endl;
   cout << "OBSTACLE AVOIDANCE : 4" << endl;
   cout << "Stay in Path       : 5" << endl;
   cout << "FLOCK              : 6" << endl;
   cout << "WANDER             : 7" << endl;
   cout << "FLEE               : 8" << endl;
   cout << "PURSUIT            : 9" << endl;
   cout << "EVADE              : 10" << endl;
   cin >> mode;
}

void createStaticAgents(){
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

void loop() {      
   view.refreshScene();   
   for(auto it = agents.begin(); it < agents.end(); it++){          
      if(mode == AVOID_OBSTACLE){
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
      (*it).updatePosition((*it).arrive);        
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

   if(mode == AVOID_OBSTACLE){
      createStaticAgents();
      createObstacle(obstacles);
      scenario = "OBSTACLE AVOIDANCE";
   }

   view = graphics(); 
   view.initGraphics(argv, argc, loop);
}


int main(int argc, char** argv) {    
   menu();  
   //init(&argc, argv, loop); 

   if(mode == FOLLOW_MOUSE){
      mouseFollower mf;
      mf.initGL(&argc, argv);
   }
   else if(mode == STAY_IN_FIELD){
      prison pr;
      pr.initGL(&argc, argv);
   }
   else if(mode == IN_FLOW_FIELD){
      windy wnd;
      wnd.initGL(&argc, argv);
   }
   else if(mode == WANDER){
      wander wndr;
      wndr.initGL(&argc, argv);
   }
   else if(mode == PURSUIT){  
      pursuit prs;
      prs.initGL(&argc, argv);
   }
   else if(mode == FLEE){
      flee fl;
      fl.initGL(&argc, argv);
   }
   else if(mode == EVADE){
      evade ev;
      ev.initGL(&argc, argv);
   }
   else if(mode == FLOCK){
      flock flc;
      flc.initGL(&argc, argv);
   }
   else if(mode == STAY_IN_PATH){
      pathFollower ptf;
      ptf.initGL(&argc, argv);
   }

   return 0;
}


