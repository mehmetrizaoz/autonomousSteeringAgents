#include "scenario.h"
#include "obstacleAvoidance.h"
#include <iostream>
#include <GL/glut.h>

using namespace std;

vector<obstacle> obstacleAvoidance::obstacles;

void obstacleAvoidance::loop(){
    for(auto it = agents.begin(); it < agents.end(); it++){
        for(auto it = obstacles.begin(); it < obstacles.end(); it++){
            point p = (*it).p;
            view.drawCircle(p, (*it).r);
        }

        (*it).targetPoint = view.getMousePosition();
        pvector seek  = behavior.seek(*it);
        seek.mul(0.5);

        pvector avoid = behavior.avoid(obstacles, *it);
        (*it).force = avoid + seek;   
        (*it).arrive = true;
    }            
    refresh();
}

void obstacleAvoidance::createObstacle(vector<obstacle> &obstacles){   
    obstacles.push_back(obstacle(point(0,0), 8));   
    obstacles.push_back(obstacle(point(-20,0), 3));  
    obstacles.push_back(obstacle(point(20,-10), 4));
}

obstacleAvoidance::obstacleAvoidance(){    
    name = "avoid obstacles";
    createAgent(STATIC, 0, 0, 0);
    createObstacle(obstacles);    
    callback = reinterpret_cast <void(*)()> ( (void *)(&loop) );
}