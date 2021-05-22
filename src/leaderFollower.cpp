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
    int k=1;
    int j=0;
    int t=3;
    point p = leaderPosition + leaderVelocity;
    //cout << "sss" << endl;
    for(auto it = agents.begin(); it < agents.end(); it++){        
        if((*it).getName() == "leader"){
            (*it).setTarget(view.getMousePosition());
            (*it).force  = behavior.seek(*it);
            leaderVelocity = (*it).getVelocity();
            leaderVelocity.mul(-1);
            leaderVelocity.normalize().mul(10);
            leaderPosition = (*it).position;
            
            view.drawText((*it).getName(), point(leaderPosition.x -3, leaderPosition.y - 3));
        }
        else{
            pvector sep = behavior.separation(agents, *it, 3);
            sep.mul(15);
            (*it).force = sep;

            if(j==k){
                //cout << j << endl;
                k++;                
                point pp = leaderPosition + leaderVelocity;
                p.y = pp.y + t*(k-1);
                p.x = p.x - t;
                //cout << "-" << endl;
                j=0;
            }
            //p.print("d");
            //cout << "j" << j << endl;
            view.drawPoint(leaderPosition + leaderVelocity);
            //(*it).setTarget(leaderPosition + leaderVelocity);
            view.drawPoint(p);
            (*it).setTarget(p);
            p.y = p.y - 2 * t; 
            j++;
            (*it).force += behavior.seek(*it);            
        }    
        (*it).arrive = true;
    }            
    refresh();
}

leaderFollower::leaderFollower()
{
    int agentCount = 15;
    float maxForce = 0.4;
    float maxSpeed = 0.4;       
    name = "leader following";

    //todo: refactor leader creation
    agent agent1 {-10.0,  0.0};
    agent1.id = 1;
    agent1.setName("leader");
    agent1.setColor(BLUE);
    agent1.setFeatures(0.8, 0.4, 5, 1);
    agents.push_back(agent1);

    createRandomAgents(agentCount, maxForce, maxSpeed);
    callback = reinterpret_cast <void(*)()> ( (void *)(&loop) );
}