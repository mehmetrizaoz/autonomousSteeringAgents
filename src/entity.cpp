#include "entity.h"

entity::entity(){
    entityColor = RED;
}


string entity::getName(){
   return name;
}

void entity::setName(string n){
   name = n;
}

int entity::getId(){
    return id;
}

void entity::setId(int i){
    id = i;
}
