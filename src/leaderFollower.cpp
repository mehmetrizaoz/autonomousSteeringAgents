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
            leaderVelocity.normalize().mul(20);
            leaderPosition = (*it).position;
            
            view.drawText((*it).getName(), point(leaderPosition.x -3, leaderPosition.y - 3));

        }
        else{            
            (*it).targetPoint = leaderPosition + leaderVelocity;            
            view.drawCircle((*it).targetPoint, 8, RED);         
            
            pvector sep = behavior.separation(agents, *it, 3);
            sep.mul(15);
            (*it).force = sep;

/*
            pvector leaderDiff = (*it).position - leaderPosition;        
            if(leaderDiff.magnitude() < 5){
                pvector fle = behavior.evade(agents, *it, view, "leader");
                fle.mul(40);
                (*it).force += fle;
            }*/

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
    int agentCount = 4;
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


    createRandomAgents(agentCount, maxForce, maxSpeed);
    callback = reinterpret_cast <void(*)()> ( (void *)(&loop) );
}