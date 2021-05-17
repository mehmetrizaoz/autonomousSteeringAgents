#include "entity.h"

entity::entity(){
    entityColor = RED;
}

string entity::getName(){
   return name;
}

void entity::setName(string name){
   this->name = name;
}

int entity::getId(){
    return id;
}

void entity::setId(int id){
    this->id = id;
}
