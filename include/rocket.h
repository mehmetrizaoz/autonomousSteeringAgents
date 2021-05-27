/**
 * @file   rocket.h
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  agents that uses genetic algorithm
 * @date   27.05.2021
*/

#pragma once

#include "pvector.h"
#include "point.h"
#include "DNA.h"

class rocket{
public:
   point position;
   pvector velocity;
   pvector acceleration;
   point target; //!

   float r; //use in display
   float fitness;
   DNA dna;
   int geneCounter = 0;
   bool hitTarget = false;
  
   rocket(pvector location, DNA dna);
   void calcFitness();
   void run();
   void checkTarget();
   void applyForce(pvector f);
   void update();
   void display();
   float getFitness();
   DNA getDNA();

};