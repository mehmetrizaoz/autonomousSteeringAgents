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
point sss;

void leaderFollower::loop()
{
    int k=1;
    int j=0;
    int t=3;
    point p1 = point(10,0);//leaderPosition + leaderVelocity;

    //point ppp = point(1,0);
    //ppp.rotate(45);
    //ppp.print("ee");
    
    /*pvector kss = pvector(5,0);
    float dd = kss.getAngle();
    cout << "dd" << dd << endl;*/
    //cout << "sss" << endl;
    for(auto it = agents.begin(); it < agents.end(); it++){      
        if((*it).getName() == "leader"){
            /*(*it).setTarget(view.getMousePosition());
            (*it).force  = behavior.seek(*it);*/
            leaderVelocity = (*it).getVelocity();
            leaderVelocity.mul(-1);
            leaderVelocity.normalize().mul(10);
            leaderPosition = (*it).position;            
            leaderAngle = leaderVelocity.getAngle();

            sss = leaderPosition + leaderVelocity;
            view.drawText((*it).getName(), point(leaderPosition.x -3, leaderPosition.y - 3));
        }
        else{
            /*pvector sep = behavior.separation(agents, *it, 3);
            sep.mul(15);
            (*it).force = sep;*/

            if(j==k){
                k++;                
                point pp = point(10,0);//leaderPosition + leaderVelocity;
                p1.y = pp.y + t*(k-1);
                p1.x = p1.x - t;
                j=0;
            }
            view.drawLine(point(0,-30), point(0,30), GREEN);
            view.drawLine(point(-30,0), point(30,0), GREEN);
           
            (*it).targetPoint = p1;
            view.drawPoint((*it).targetPoint, RED);
            //(*it).force += behavior.seek(*it);
            //p1.print("");
            p1.y = p1.y - 2 * t; 
            j++;
        }   
        (*it).arrive = true;
    }       

    for(auto it = agents.begin(); it < agents.end(); it++){
        if((*it).getName() == "leader"){}
        else{
            cout << endl;
            (*it).targetPoint.print("p");
            float diff = (10 - (*it).targetPoint.x) * (10 - (*it).targetPoint.x);
            diff      += (0  - (*it).targetPoint.y) * (0  - (*it).targetPoint.y);
            diff       = sqrt(diff);
            cout << "diff " << diff << endl;
            
            pvector mm = (*it).targetPoint - point(10,0);
            float ang = mm.getAngle();
            cout << "ang" << ang << endl;
            
            (*it).targetPoint.x = diff * cos((ang + 45) * PI / 180);
            (*it).targetPoint.y = diff * sin((ang + 45) * PI / 180);

            (*it).targetPoint = point(10, 0) + (*it).targetPoint;
            (*it).targetPoint.print("pt");

            view.drawPoint((*it).targetPoint, BLUE);

            //(*it).force += behavior.seek(*it);
        }
    }
    cout << "---" << endl << endl;
    refresh();
}

leaderFollower::leaderFollower()
{
    int agentCount = 3;
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