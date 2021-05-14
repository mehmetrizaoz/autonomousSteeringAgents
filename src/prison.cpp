#include "scenario.h"
#include "prison.h"
#include <iostream>
#include <GL/glut.h>

using namespace std;

void prison::loop(){
    for(auto it = agents.begin(); it < agents.end(); it++){
         view.drawWall(WALL, myColor);  
         (*it).force  = behavior.stayInArea(*it, WALL - DISTANCE);
         (*it).force += behavior.separation(agents, *it);         
    }            
    refresh();
}

prison::prison(){    
    int agentCount = 30;
    float maxForce = 0.5;
    float maxSpeed = 0.6;       

    name = "stay in prison";
    createAgent(RANDOM, &agentCount, &maxForce, &maxSpeed); 
    callback = reinterpret_cast <void(*)()> ( (void *)(&loop) );
}