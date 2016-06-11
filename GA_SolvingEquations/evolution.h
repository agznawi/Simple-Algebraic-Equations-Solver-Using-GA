#ifndef EVOLUTION_H
#define EVOLUTION_H

#include "individual.h"
#include "population.h"

class Evolution
{
public:
    static int divPrecesion;
    static int maxMutationSize;
    static Individual crossover(Individual indiv1, Individual indiv2);
    static void mutate(Individual &indiv);
    static void calculateFitness(Individual &indiv);
};

#endif // EVOLUTION_H
