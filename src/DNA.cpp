#include "DNA.h"
#include "math.h"
#include <iostream>

using namespace std;

DNA::DNA(int lifetime){
    srand(time(NULL));    

    for(int i=0; i<lifetime; i++){
        float angle = rand() % 360;
        pvector pv = pvector(cos(angle * PI / 180), sin(angle * PI / 180)) ;
        pv.mul(maxForce);
        genes.at(i) = pv;
    }
}

DNA::DNA(vector<pvector> &newgenes){
    genes = newgenes;
}

DNA DNA::crossover(DNA partner){
    vector<pvector> child;
    int crossover = int(rand() % genes.size());

    for(int i=0; i<genes.size(); i++){
        if(i>crossover)
           child.at(i) = genes.at(i);
        else
           child.at(i) = partner.genes.at(i);
    }
    
    DNA newgenes = DNA(child); 
    return newgenes;
}

void DNA::mutate(float m){
    for (int i = 0; i < genes.size(); i++) {
        if ( (rand() % 1) < m) {
            float angle = rand() % 360;
            pvector pv = pvector(cos(angle * PI / 180), sin(angle * PI / 180)) ;
            pv.mul(maxForce);
            genes.at(i) = pv;
        }
    }
}
