#include "scenario.h"
#include "flock.h"
#include <iostream>
#include <GL/glut.h>

using namespace std;

void flock::loop()
{
    for(auto it = agents.begin(); it < agents.end(); it++){
         view.forceInScreen((*it));
         
         pvector sep = behavior.separation(agents, *it);
         sep.mul(1.5);         
         pvector ali = behavior.align(agents, *it);
         ali.mul(4);    
         pvector coh = behavior.cohesion(agents, *it);
         coh.mul(0.1);

         (*it).force = sep + ali + coh;
         (*it).desiredVelocity = (*it).force + (*it).velocity;
         (*it).targetPoint = (*it).position + (*it).desiredVelocity;
         (*it).arrive = true;
    }
            
    refresh();
}

flock::flock()
{
    int agentCount = 50;
    float maxForce = 0.3;
    float maxSpeed = 0.8;
    name = "flocking agents";    
    createAgent(RANDOM, &agentCount, &maxForce, &maxSpeed);
    callback = reinterpret_cast <void(*)()> ( (void *)(&loop) );
}