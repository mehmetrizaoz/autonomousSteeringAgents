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

pvector leaderVelocity;
point leaderPosition;
point ahead;

void leaderFollower::loop()
{
    for(auto it = agents.begin(); it < agents.end(); it++){
        if((*it).getName() == "leader"){
            (*it).targetPoint = view.getMousePosition();
            (*it).force  = behavior.seek(*it);  
            leaderVelocity = (*it).velocity;  
            leaderVelocity.mul(-1);
            leaderPosition = (*it).position;  

            pvector tmp = (*it).velocity;
            tmp.normalize().mul(10);
            ahead = (*it).position + tmp;            
        }
        else{//lion            
            leaderVelocity.normalize();
            leaderVelocity.mul(15);
            (*it).targetPoint = leaderPosition + leaderVelocity;
            
            view.drawPoint((*it).targetPoint);
            view.drawCircle((*it).targetPoint, 6, RED);
            
            pvector pur = behavior.seek(*it);                               
            pvector sep = behavior.separation(agents, *it);            
            sep.mul(20);           
            
            pvector diff = (*it).position - (*it).targetPoint;
            if(diff.magnitude() > 3){
                (*it).force = sep + pur;
            }
            else{
                (*it).force = pvector(0,0);                
            }
        }
        (*it).arrive = true;
    }            
    refresh();
}

leaderFollower::leaderFollower()
{
    int agentCount = 2;
    float maxForce = 0.2;
    float maxSpeed = 0.4;       
    name = "leader following";

    agent agent1 {-10.0,  0.0};
    agent1.id = 1;
    agent1.setName("leader");    
    agent1.entityColor = BLUE;
    agent1.setFeatures(0.8, 0.4, 5, 1);
    agents.push_back(agent1);


    createAgent(RANDOM, &agentCount, &maxForce, &maxSpeed);
    callback = reinterpret_cast <void(*)()> ( (void *)(&loop) );
}