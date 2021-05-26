/**
 * @file   DNA.h
 * @author Mehmet Rıza Öz - mehmetrizaoz@gmail.com
 * @brief  
 * @date   26.05.2021
*/

#pragma once

#include "pvector.h"
#include <vector>

#define PI          3.14159265

class DNA {
public:
   vector<pvector> genes;
   float maxForce = 0.1;
   DNA(int lifetime);
   DNA(vector<pvector> &newgenes);
   DNA crossover(DNA partner);
   void mutate(float m);
};