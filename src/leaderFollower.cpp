/**
 * @file   leaderFollower.cpp
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  leaderFollower class implementation
 * @date   23.05.2021
*/

#include "scenario.h"
#include "leaderFollower.h"
#include <iostream>
#include <GL/glut.h>
#include "math.h"

using namespace std;

pvector leaderFollower::leaderVelocity;
point leaderFollower::leaderPosition;
float leaderFollower::leaderAngle;
point mainTarget;

void leaderFollower::loop()
{   //todo: refactor code
    int row = 1;
    int index = 0;
    int distance = 3;
    point vTarget = mainTarget;

    for(auto it = agents.begin(); it < agents.end(); it++){      
        if((*it).getName() == "leader"){
            (*it).setTarget(view.getMousePosition());
            (*it).force  = behavior.seek(*it);
            
            leaderVelocity = (*it).getVelocity();
            leaderVelocity.mul(-1);
            leaderVelocity.normalize().mul(10);
            leaderPosition = (*it).position;            
            leaderAngle = leaderVelocity.getAngle() + 180;

            mainTarget = leaderPosition + leaderVelocity;
            view.drawText((*it).getName(), point(leaderPosition.x -3, leaderPosition.y - 3));
        }
        else{
            pvector sep = behavior.separation(agents, *it, 3);
            sep.mul(20);
            (*it).force = sep;
            
            //make target of the agents different and v shaped individually
            if(index == row){
                row++;        
                vTarget = point( vTarget.x - distance, mainTarget.y + distance * ( row - 1 ) );
                index = 0;
            }
            index++;            
            (*it).targetPoint = vTarget;
            //view.drawPoint((*it).targetPoint, RED);
            vTarget.y = vTarget.y - ( 2 * distance );            

            //transform other agent targets referencing first agents target considering leader angle
            (*it).targetPoint.rotateByAngleAboutPoint(mainTarget, leaderAngle);

            view.drawPoint((*it).targetPoint, BLUE);
            (*it).force += behavior.seek(*it);

            //todo: make angle of the agent same with angle of leader
            //todo: leader changes its orientation before arriving
        }   
        (*it).arrive = true;
    }       
    refresh();
}

leaderFollower::leaderFollower()
{
    int agentCount = 10;
    float maxForce = 0.1;
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