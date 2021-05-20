/**
 * @file   evade.cpp
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  evade class implementation
 * @date   15.05.2021
*/

#include "scenario.h"
#include "evade.h"
#include <iostream>
#include <GL/glut.h>

using namespace std;

void evade::loop()
{
    for(auto it = agents.begin(); it < agents.end(); it++){
         if((*it).getName() == "lion"){
            (*it).targetPoint = view.getMousePosition();
            (*it).force  = behavior.seek(*it);
            (*it).arrive = true;
         }
         else{//gazelle
            (*it).force  = behavior.evade(agents, *it, view, "lion");
         }
    }
            
    refresh();
}

evade::evade()
{
    name = "evading";
    createStaticAgents("gazelle", "lion");
    callback = reinterpret_cast <void(*)()> ( (void *)(&loop) );
}