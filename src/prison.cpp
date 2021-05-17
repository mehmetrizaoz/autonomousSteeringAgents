/**
 * @file   prison.cpp
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  prison class implementation
 * @date   15.05.2021
*/

#include "scenario.h"
#include "prison.h"
#include <iostream>
#include <GL/glut.h>

#define WALL        30
#define DISTANCE    2

using namespace std;

void prison::loop()
{
    for(auto it = agents.begin(); it < agents.end(); it++){
        view.drawLine(point(-WALL,  WALL), point( WALL,  WALL), BLUE);
        view.drawLine(point( WALL,  WALL), point( WALL, -WALL), BLUE);
        view.drawLine(point( WALL, -WALL), point(-WALL, -WALL), BLUE);
        view.drawLine(point(-WALL,  WALL), point(-WALL, -WALL), BLUE);
        (*it).force  = behavior.stayInArea(*it, WALL - DISTANCE);
        (*it).force += behavior.separation(agents, *it);         
    }            
    refresh();
}

prison::prison()
{
    int agentCount = 30;
    float maxForce = 0.6;
    float maxSpeed = 0.6;       

    name = "stay in prison";
    createAgent(RANDOM, &agentCount, &maxForce, &maxSpeed); 
    callback = reinterpret_cast <void(*)()> ( (void *)(&loop) );
}