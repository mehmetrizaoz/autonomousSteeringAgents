#include "scenario.h"
#include "pursuit.h"
#include <iostream>
#include <GL/glut.h>

using namespace std;

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
    createAgent(STATIC, nullptr, nullptr, nullptr);
    callback = reinterpret_cast <void(*)()> ( (void *)(&loop) );
}