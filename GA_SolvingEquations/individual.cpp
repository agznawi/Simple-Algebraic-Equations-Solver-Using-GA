#include "individual.h"
#include "randengine.h"

#include <random>
using std::uniform_int_distribution;

Individual::Individual()
    : fitness(0)
{
    randomize();
}

Individual::Individual(float variables[])
    : fitness(0)
{
    for(int i = 0; i < numVariables; i++)
        Individual::variables[i] = variables[i];
}

void Individual::randomize()
{
    uniform_int_distribution<int> rVal(-variableRange, variableRange);

    for(int i = 0; i < numVariables; i++)
    {
        variables[i] = rVal(e1);
    }
}


float Individual::getFitness()
{
    return fitness;
}

void Individual::setFitness(float f)
{
    fitness = f;
}
