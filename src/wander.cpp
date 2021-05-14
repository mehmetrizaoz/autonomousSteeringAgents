#include "scenario.h"
#include "wander.h"
#include <iostream>
#include <GL/glut.h>

using namespace std;

void wander::loop(){
    for(auto it = agents.begin(); it < agents.end(); it++){
       (*it).force = behavior.wander(*it);
    }
            
    refresh();
}

wander::wander(){    
    name = "wandering objects";
    createAgent(RANDOM, 30, 0.3, 0.6);   
    callback = reinterpret_cast <void(*)()> ( (void *)(&loop) );
}