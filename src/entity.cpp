/**
 * @file   entity.cpp
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  entity class implementation
 * @date   18.05.2021
*/

#include "entity.h"

entity::entity(){
    entityColor = RED;
}


color entity::getColor()
{
   return entityColor;
}
   
void entity::setColor(color color){
    entityColor = color;
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
