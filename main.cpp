#include <iostream>
#include "mouseFollower.h"
#include "prison.h"
#include "windy.h"
#include "wander.h"
#include "pursuit.h"
#include "flee.h"
#include "evade.h"
#include "flock.h"
#include "pathFollower.h"
#include "obstacleAvoidance.h"

using namespace std;

int mode;

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

int main(int argc, char** argv) {    
   menu();  

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
   else if(mode == AVOID_OBSTACLE){
      obstacleAvoidance obst;
      obst.initGL(&argc, argv);
   }

   return 0;
}


