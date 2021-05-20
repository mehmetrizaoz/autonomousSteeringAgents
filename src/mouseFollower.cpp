/**
 * @file   mouseFollower.cpp
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  mouseFollower class implementation
 * @date   15.05.2021
*/

#include "scenario.h"
#include "mouseFollower.h"
#include <iostream>
#include <GL/glut.h>

using namespace std;

void mouseFollower::loop()
{
    for(auto it = agents.begin(); it < agents.end(); it++){
       (*it).targetPoint = view.getMousePosition();
       (*it).force  = behavior.seek(*it);
       (*it).arrive = true;
    }            
    refresh();
}

mouseFollower::mouseFollower()
{
    int agentCount = 30;
    float maxForce = 0.3;
    float maxSpeed = 0.6;       
    name = "mouse following";
    createRandomAgents(agentCount, maxForce, maxSpeed);
    callback = reinterpret_cast <void(*)()> ( (void *)(&loop) );
}