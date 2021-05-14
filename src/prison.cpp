#include "scenario.h"
#include "prison.h"
#include <iostream>
#include <GL/glut.h>

using namespace std;

void prison::initGL(int* argc, char** argv){    
    view.initGraphics(argc, argv, callback);
}

void prison::loop(){
    for(auto it = agents.begin(); it < agents.end(); it++){
         view.drawWall(WALL, myColor);  
         (*it).force  = behavior.stayInArea(*it, WALL - DISTANCE);
         (*it).force += behavior.separation(agents, *it);         
    }            
    refresh();
}

prison::prison(){    
    name = "stay in prison";
    createAgent(RANDOM, 30, 0.5, 0.5); 
    callback = reinterpret_cast <void(*)()> ( (void *)(&loop) );
}