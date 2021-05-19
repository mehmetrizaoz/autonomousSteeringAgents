/**
 * @file   leaderFollower.cpp
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  leaderFollower class implementation
 * @date   19.05.2021
*/

#include "scenario.h"
#include "leaderFollower.h"
#include <iostream>
#include <GL/glut.h>

using namespace std;

void leaderFollower::loop()
{
    for(auto it = agents.begin(); it < agents.end(); it++){
        (*it).targetPoint = view.getMousePosition();
        (*it).force  = behavior.seek(*it);
        (*it).arrive = true;
    }            
    refresh();
}

leaderFollower::leaderFollower()
{
    int agentCount = 30;
    float maxForce = 0.3;
    float maxSpeed = 0.6;       
    name = "leader following";
    createAgent(RANDOM, &agentCount, &maxForce, &maxSpeed);
    callback = reinterpret_cast <void(*)()> ( (void *)(&loop) );
}