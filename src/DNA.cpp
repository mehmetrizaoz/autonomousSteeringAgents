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
        genes.push_back(pv);
    }

}

DNA::DNA(vector<pvector> &newgenes){
    genes = newgenes;
}

DNA::DNA(){
    
}

DNA DNA::crossover(DNA partner){
    vector<pvector> child;
    int crossover = int(rand() % genes.size());

    for(int i=0; i<genes.size(); i++){
        if(i>crossover)
           child.push_back(genes.at(i));
        else
           child.push_back(partner.genes.at(i));
    }
    
    DNA newgenes = DNA(child); 
    return newgenes;
}

void DNA::mutate(float m){
    float i = rand() % 10;
    i /= float(10);
    for (int i = 0; i < genes.size(); i++) {
        float temp = rand() % 10;
        temp /= float(10);        
        if ( temp < m ) {            
            float angle = rand() % 360;
            pvector pv = pvector(cos(angle * PI / 180), sin(angle * PI / 180)) ;
            pv.mul(maxForce);
            genes.at(i) = pv;
        }
    }
}
