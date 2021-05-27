/**
 * @file   scenario.cpp
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  scenario base class implementation
 * @date   15.05.2021
*/

#include "scenario.h"
#include "random.h"
#include "entity.h"
#include <iostream>
#include <string> 

#define MAX_NUMBER_OF_AGENTS 50

using namespace std;

vector<agent> scenario::agents;
graphics scenario::view;
steeringBehavior scenario::behavior;
string scenario::name;

void scenario::initGL(int* argc, char** argv)
{    
    view.initGraphics(argc, argv, callback);
}

scenario::scenario()
{
    view = graphics(); 
}

void scenario::refresh()
{
    point textPosition = point(-34, 32.25);
    
    for(auto it = agents.begin(); it < agents.end(); it++){       
       (*it).draw(view);
    }
      
    view.drawText(name, textPosition);
    view.refreshScene(); 
}

void scenario::createRandomAgents(int count, const float force, const float speed)
{
   int size = MAX_NUMBER_OF_AGENTS * 2;   
   int arr[size];

   srand(time(NULL));
   random::createRandomArray(arr, size);
   
   agent tempAgent {0, 0};
   for(int i=0; i < count * 2; i=i+2){
      tempAgent.setName("agent"+to_string(i)+":");
      tempAgent.position.x = arr[i]   - WIDTH;
      tempAgent.position.y = arr[i+1] - HEIGHT;

      //float f = (float) arr[i] / (float) 100.0;
      //float s = (float) arr[i+1] / (float) 100.0;
      //if( f > force ) f = force;
      //if( s > speed ) s = speed;
      //if( s > f ) s = f;
      
      tempAgent.setColor(color::getColor((i/2) % 8));
      tempAgent.setFeatures(speed, force, 5, 1); 
      agents.push_back(tempAgent);
   }
}

void scenario::createStaticAgents(string s1, string s2)
{
    agent agent1 {-10.0,  0.0};
    agent1.id = 1;
    agent1.setName(s1);    
    agent1.setColor(BLUE);
    agent1.setFeatures(0.5, 0.2, 5, 1);
    agents.push_back(agent1);

    agent agent2 { 10.0,  0.0};
    agent2.id = 2;
    agent2.setName(s2);
    agent2.setColor(RED);
    agent2.setFeatures(0.4, 0.2, 5, 1);    
    agents.push_back(agent2);
}

void scenario::createTroop(int count)
{
    int row = 14;
    int blanks = 5;
    int rowStartPosition = -33;
    agent tempAgent {0, 0};
    pvector location {-33, 33};
   
    for(int i=0; i < count; i++){
        tempAgent.id = i;
        tempAgent.setVelocity(pvector(0, 0));
        tempAgent.position.x = location.x;
        tempAgent.position.y = location.y;
        tempAgent.setTarget(tempAgent.position);

        if( ((i+1) % row) == 0){
           location.y -= blanks;
           location.x  = rowStartPosition;
        }
        else
           location.x += blanks; 
        
        tempAgent.setColor(color::getColor((i/2) % 8));
        tempAgent.setFeatures(0.3, 0.3, 5, 1);
        agents.push_back(tempAgent);
    }
}
