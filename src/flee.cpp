#include "scenario.h"
#include "flee.h"
#include <iostream>
#include <GL/glut.h>

using namespace std;

void flee::initGL(int* argc, char** argv){    
    void(* callback)();
    callback = reinterpret_cast <void(*)()> ( (void *)(&loop) );
    view.initGraphics(argc, argv, callback);
}

void flee::loop(){
    for(auto it = agents.begin(); it < agents.end(); it++){
        (*it).force = behavior.flee((*it), view, view.getMousePosition());
    }
            
    refresh();
}

flee::flee(){    
    name = "fleeing troop";    
    createAgent(TROOP, 196, 0, 0);
}