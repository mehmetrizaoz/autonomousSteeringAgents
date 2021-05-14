#include <iostream>
#include "mouseFollower.h"
#include "prison.h"
#include "windy.h"
#include "wander.h"
#include "pursuit.h"
#include "flee.h"
#include "scenario.h"
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

   scenario* sc;

   if(mode == FOLLOW_MOUSE){
      *sc = mouseFollower();      
   }
   else if(mode == STAY_IN_FIELD){
      *sc = prison();
   }
   else if(mode == IN_FLOW_FIELD){
      *sc = windy();      
   }
   else if(mode == WANDER){
      *sc = wander();
   }
   else if(mode == PURSUIT){  
      *sc = pursuit();
   }
   else if(mode == FLEE){
      *sc = flee();
   }
   else if(mode == EVADE){
      *sc = evade();
   }
   else if(mode == FLOCK){
      *sc = flock();
   }
   else if(mode == STAY_IN_PATH){
      *sc = pathFollower();
   }
   else if(mode == AVOID_OBSTACLE){
      *sc = obstacleAvoidance();
   }

   sc->initGL(&argc, argv);

   return 0;
}
