/**
 * @file   obstacleAvoidance.cpp
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  obstacleAvoidance class implementation
 * @date   15.05.2021
*/

#include "scenario.h"
#include "obstacleAvoidance.h"
#include <iostream>
#include <GL/glut.h>

using namespace std;

vector<obstacle> obstacleAvoidance::obstacles;

void obstacleAvoidance::loop()
{
    for(auto it = agents.begin(); it < agents.end(); it++){
        if(view.clicked == true){
            cout << "clicked" << endl;
            view.clickPosition.print("pos");
            obstacles.push_back(obstacle(view.clickPosition, 4));
            view.clicked = false;
        }

        (*it).setTarget(view.getMousePosition());
        pvector seek  = behavior.seek(*it);
        seek.mul(0.5);

        pvector avoid = behavior.avoid(obstacles, *it);
        (*it).force = avoid + seek;   
        (*it).arrive = true;        
    }            
    //cout << "-------" << endl;
    for(auto it = obstacles.begin(); it < obstacles.end(); it++){            
        //cout << (*it).getRadius() << endl;
        //(*it).getCenter().print("center:");
        (*it).draw(view);
    }

    refresh();
}

void obstacleAvoidance::createObstacle(vector<obstacle> &obstacles)
{
    obstacles.push_back(obstacle(point(0,0), 8));
    obstacles.push_back(obstacle(point(-20,0), 3));  
    obstacles.push_back(obstacle(point(20,-10), 4));
}

obstacleAvoidance::obstacleAvoidance()
{
    name = "avoid obstacles";
    createStaticAgents("ag1", "ag2");
    createObstacle(obstacles);    
    callback = reinterpret_cast <void(*)()> ( (void *)(&loop) );
}