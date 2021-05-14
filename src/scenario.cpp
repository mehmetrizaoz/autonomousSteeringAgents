#include "scenario.h"
#include "random.h"
#include <iostream>

using namespace std;

vector<agent> scenario::agents;
graphics scenario::view;
steeringBehavior scenario::behavior;
color scenario::myColor; 
string scenario::name;

scenario::scenario()
{
    srand(time(NULL));
    myColor.createColors();
    view = graphics(); 
}

void scenario::refresh(){
    for(auto it = agents.begin(); it < agents.end(); it++){       
       (*it).updatePosition((*it).arrive);
       view.drawAgent(*it, (*it).fillColor);
    }
      
    view.drawText(name, point(-34, 32.25)); //TODO: magic numbers, define left corner
    view.refreshScene(); 
}

void scenario::createRandomAgents(int count, const float force, const float speed)
{
   int size = MAX_NUMBER_OF_AGENTS * 2;   
   int arr[size];
   random::createRandomArray(arr, size);
   agent tempAgent {0, 0};

   for(int i=0; i < count * 2; i=i+2){
      tempAgent.position.x = arr[i]   - WIDTH;
      tempAgent.position.y = arr[i+1] - HEIGHT;
      tempAgent.fillColor = myColor.colors.at( (i/2) % 8 );
      tempAgent.setFeatures(speed, force, 5, 1); 
      agents.push_back(tempAgent);
   } 
}

void scenario::createStaticAgents()
{
    agent agent1 {-10.0,  0.0};
    agent1.id = 1;
    agent1.name = "gazelle";    
    agent1.fillColor = myColor.getColor(BLUE);
    agent1.setFeatures(0.5, 0.2, 5, 1);
    agents.push_back(agent1);

    agent agent2 { 10.0,  0.0};
    agent2.id = 2;
    agent2.name = "lion";
    agent2.fillColor = myColor.getColor(YELLOW);
    agent2.setFeatures(0.4, 0.2, 5, 1);    
    agents.push_back(agent2);
}


void scenario::createTroop(int count)
{
    //TODO: magic numbers
    agent tempAgent {0, 0};
    pvector location {-33, 33};
   
    for(int i=0; i < count; i++){
        tempAgent.id = i;
        tempAgent.velocity = pvector(0, 0);
        tempAgent.position.x = location.x;
        tempAgent.position.y = location.y;
        tempAgent.targetPoint = tempAgent.position;                 

        if( ((i+1) % 14) == 0){
           location.y -= 5;
           location.x  = -33;
        }
        else
           location.x += 5; 

        tempAgent.fillColor = myColor.colors.at( (i/2) % 8 );
        tempAgent.setFeatures(0.3, 0.3, 5, 1);
        agents.push_back(tempAgent);
    }
}

void scenario::createAgent(int type, int count, float force, float speed)
{
    if(type == TROOP){
        createTroop(count);
    }
    else if(type == RANDOM){
        createRandomAgents(count, force, speed);
    }
    else if(type == STATIC){
        createStaticAgents();
    }
    else{
        //error message   
    }
}
