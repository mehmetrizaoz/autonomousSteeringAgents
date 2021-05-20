/**
 * @file   flee.cpp
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  flee class implementation
 * @date   15.05.2021
*/

#include "scenario.h"
#include "flee.h"
#include <iostream>
#include <GL/glut.h>

using namespace std;

void flee::loop()
{
    for(auto it = agents.begin(); it < agents.end(); it++){
        (*it).force = behavior.flee((*it), view, view.getMousePosition());
    }
            
    refresh();
}

flee::flee()
{
    int agentCount = 196;
    name = "fleeing troop";    
    createTroop(agentCount);
    callback = reinterpret_cast <void(*)()> ( (void *)(&loop) );
}