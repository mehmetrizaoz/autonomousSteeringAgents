#include "scenario.h"
#include "windy.h"
#include <iostream>
#include <GL/glut.h>

using namespace std;

flowField windy::flow;

void windy::initGL(int* argc, char** argv){    
    view.initGraphics(argc, argv, callback);
}

void windy::loop(){
    for(auto it = agents.begin(); it < agents.end(); it++){
         flow = flowField(pvector(GRAVITY));
         (*it).force  = behavior.inFlowField(*it, flow);
         
         flow = flowField(pvector(WIND_WEST));
         (*it).force += behavior.inFlowField(*it, flow);
    }            
    refresh();
}

windy::windy(){    
    name = "flow field";
    createAgent(RANDOM, 30, 0.3, 0.6);  
    callback = reinterpret_cast <void(*)()> ( (void *)(&loop) );
}