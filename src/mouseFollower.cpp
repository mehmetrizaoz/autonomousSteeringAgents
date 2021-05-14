#include "scenario.h"
#include "mouseFollower.h"
#include <iostream>
#include <GL/glut.h>

using namespace std;

void mouseFollower::loop(){
    for(auto it = agents.begin(); it < agents.end(); it++){
       (*it).targetPoint = view.getMousePosition();
       (*it).force  = behavior.seek(*it);
       (*it).arrive = true;
    }            
    refresh();
}

mouseFollower::mouseFollower(){    
    name = "mouse following";
    createAgent(RANDOM, 30, 0.3, 0.6);
    callback = reinterpret_cast <void(*)()> ( (void *)(&loop) );
}