#include "rocket.h"


rocket::rocket(pvector location, DNA dna){
   acceleration = pvector(0,0);
   velocity = pvector(0,0);
   position.x = location.x;
   position.y = location.y;
   r = 4;
   this->dna = dna;

}

void rocket::calcFitness(){
    float d = position.difference(target);
    this->fitness = (1/d) * (1/d);
}


void rocket::run(){
    checkTarget();
    if( hitTarget == false ){
        applyForce(dna.genes[geneCounter]);
        geneCounter++;
        geneCounter %= dna.genes.size();
        update();
    }
    display();
}

void rocket::checkTarget(){
    float d = position.difference(target);
    if(d < 12){
        hitTarget = true;
    }
}

void rocket::applyForce(pvector f){
    acceleration.add(f);
}

void rocket::update(){
    velocity.add(acceleration);
    position = position + velocity;
    acceleration = pvector(0,0);
}

void rocket::display(){
    //diplay rocket
}

float rocket::getFitness(){
    return fitness;
}

DNA rocket::getDNA(){
    return dna;
}
