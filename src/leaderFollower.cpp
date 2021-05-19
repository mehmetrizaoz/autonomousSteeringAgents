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

pvector leaderFollower::leaderVelocity;
point leaderFollower::leaderPosition;

void leaderFollower::loop()
{
    for(auto it = agents.begin(); it < agents.end(); it++){
        if((*it).getName() == "leader"){
            (*it).targetPoint = view.getMousePosition();
            (*it).force  = behavior.seek(*it);  
            leaderVelocity = (*it).velocity;  
            leaderVelocity.mul(-1);
            leaderVelocity.normalize().mul(10);
            leaderPosition = (*it).position;
        }
        else{            
            (*it).targetPoint = leaderPosition + leaderVelocity;            
            view.drawCircle((*it).targetPoint, 8, RED);         
            
            pvector sep = behavior.separation(agents, *it);
            sep.mul(10);
            (*it).force = sep;
            
            pvector diff = (*it).position - (*it).targetPoint;
            if(diff.magnitude() > 5) { (*it).force   += behavior.seek(*it); }
            else                     { (*it).velocity = pvector(0,0);       }
        }    
        (*it).arrive = true;    
    }            
    refresh();
}

leaderFollower::leaderFollower()
{
    int agentCount = 10;
    float maxForce = 0.4;
    float maxSpeed = 0.4;       
    name = "leader following";

    //todo: refactor leader creation
    agent agent1 {-10.0,  0.0};
    agent1.id = 1;
    agent1.setName("leader");    
    agent1.entityColor = BLUE;
    agent1.setFeatures(0.8, 0.4, 5, 1);
    agents.push_back(agent1);


    createAgent(RANDOM, &agentCount, &maxForce, &maxSpeed);
    callback = reinterpret_cast <void(*)()> ( (void *)(&loop) );
}