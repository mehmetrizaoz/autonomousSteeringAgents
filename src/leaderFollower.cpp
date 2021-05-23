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
            
            if(index == row){
                row++;        
                vTarget = point( vTarget.x - distance, mainTarget.y + distance * ( row - 1 ) );
                index = 0;
            }
            
            (*it).targetPoint = vTarget;
            view.drawPoint((*it).targetPoint, RED);
            vTarget.y = vTarget.y - ( 2 * distance ); 
            index++;

            //todo make below transform parametric function in point class                  
            //--------------------------------------------------
            float diff = mainTarget.difference( (*it).targetPoint );
            pvector agentTargetToMainTarget = (*it).targetPoint - mainTarget;
            float angleAboutMainTarget = agentTargetToMainTarget.getAngle();            
            (*it).targetPoint = point (diff * cos((angleAboutMainTarget + leaderAngle) * PI / 180),
                                       diff * sin((angleAboutMainTarget + leaderAngle) * PI / 180));
            (*it).targetPoint = mainTarget + (*it).targetPoint;
            //--------------------------------------------------

            view.drawPoint((*it).targetPoint, BLUE);
            //todo: make angle of the agent same with angle of leader
            (*it).force += behavior.seek(*it);
        }   
        (*it).arrive = true;
    }       
    refresh();
}

leaderFollower::leaderFollower()
{
    int agentCount = 10;
    float maxForce = 0.4;
    float maxSpeed = 0.8;       
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