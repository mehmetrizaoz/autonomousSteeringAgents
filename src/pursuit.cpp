#include "scenario.h"
#include "pursuit.h"
#include <iostream>
#include <GL/glut.h>

using namespace std;

void pursuit::initGL(int* argc, char** argv){    
    view.initGraphics(argc, argv, callback);
}

void pursuit::loop(){
    for(auto it = agents.begin(); it < agents.end(); it++){
         if((*it).name == "gazelle"){
            (*it).targetPoint = view.getMousePosition();
            (*it).force  = behavior.seek(*it);            
         }
         else{//lion
            (*it).force  = behavior.pursuit(agents, *it, view);            
         }
         (*it).arrive = true;
    }
            
    refresh();
}

pursuit::pursuit(){    
    name = "pursuit";    
    createAgent(STATIC, 0, 0, 0);
    callback = reinterpret_cast <void(*)()> ( (void *)(&loop) );
}