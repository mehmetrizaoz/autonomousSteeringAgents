#include "scenario.h"
#include "flee.h"
#include <iostream>
#include <GL/glut.h>

using namespace std;

void flee::loop(){
    for(auto it = agents.begin(); it < agents.end(); it++){
        (*it).force = behavior.flee((*it), view, view.getMousePosition());
    }
            
    refresh();
}

flee::flee(){    
    int agentCount = 196;
    name = "fleeing troop";    
    createAgent(TROOP, &agentCount, nullptr, nullptr);
    callback = reinterpret_cast <void(*)()> ( (void *)(&loop) );
}