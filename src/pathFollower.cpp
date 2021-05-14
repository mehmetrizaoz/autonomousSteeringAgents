#include "scenario.h"
#include "pathFollower.h"
#include <iostream>
#include <GL/glut.h>

using namespace std;

path pathFollower::myPath;

void pathFollower::initGL(int* argc, char** argv){    
    void(* callback)();
    callback = reinterpret_cast <void(*)()> ( (void *)(&loop) );
    view.initGraphics(argc, argv, callback);
}

void pathFollower::loop(){
    for(auto it = agents.begin(); it < agents.end(); it++){
        view.drawPath(myPath, myColor);
        pvector seek = behavior.stayInPath_2(*it, myPath, view);
        pvector sep  = behavior.separation(agents, *it);
        sep.mul(5);         
        (*it).force = sep + seek;
    }
            
    refresh();
}

void pathFollower::createPath(path &p){
   p.addPoint(point(-40,  5));
   p.addPoint(point(-14, 15));
   p.addPoint(point( 10,  7));
   p.addPoint(point( 40, 12));
}

pathFollower::pathFollower(){    
    myPath = path(8);
    createPath(myPath); 
    name = "path following";
    createAgent(RANDOM, 40, 0.2, 0.4);
}