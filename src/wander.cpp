/**
 * @file   wander.cpp
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  wander class implementation
 * @date   15.05.2021
*/

#include "scenario.h"
#include "wander.h"
#include <iostream>
#include <GL/glut.h>

using namespace std;

void wander::loop()
{
    for(auto it = agents.begin(); it < agents.end(); it++){
       (*it).force = behavior.wander(*it);
    }
            
    refresh();
}

wander::wander()
{
    int agentCount = 30;
    float maxForce = 0.3;
    float maxSpeed = 0.6;       

    name = "wandering objects";
    createAgent(RANDOM, &agentCount, &maxForce, &maxSpeed);   
    callback = reinterpret_cast <void(*)()> ( (void *)(&loop) );
}
