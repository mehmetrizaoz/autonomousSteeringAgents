#include "scenario.h"
#include "windy.h"
#include <iostream>
#include <GL/glut.h>

using namespace std;

flowField windy::flow;

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
    int agentCount = 30;
    float maxForce = 0.3;
    float maxSpeed = 0.6;       

    name = "flow field";
    createAgent(RANDOM, &agentCount, &maxForce, &maxSpeed);  
    callback = reinterpret_cast <void(*)()> ( (void *)(&loop) );
}