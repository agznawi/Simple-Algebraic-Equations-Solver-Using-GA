#include "evolution.h"
#include "individual.h"
#include "randengine.h"

#include "math.h"
// fabs()
#include "algorithm"
using std::max;
#include <random>
using std::uniform_int_distribution;
using std::discrete_distribution;

Individual Evolution::crossover(Individual indiv1, Individual indiv2)
{
    uniform_int_distribution<int> rMix(0, 1);

    float variables[Individual::numVariables]; // Create new chromosome
    // Use half uniform crossover
    for(int i = 0; i < Individual::numVariables; i++)
    {
        if(rMix(e1))
            variables[i] = indiv1.variables[i];
        else
            variables[i] = indiv2.variables[i];
    }

    return Individual(variables);
}

void Evolution::mutate(Individual &indiv)
{
    uniform_int_distribution<int> rVar(0, Individual::numVariables-1);
    uniform_int_distribution<int> rVal(0, maxMutationSize);
    discrete_distribution<int> rDir{-1, 1};

    indiv.variables[rVar(e1)] += rDir(e1) * rVal(e1); // Apply mutation
}

void Evolution::calculateFitness(Individual &indiv)
{
    float x = indiv.variables[0] / divPrecesion;
    float y = indiv.variables[1] / divPrecesion;
    float z = indiv.variables[2] / divPrecesion;

    float hyp1 = x * x * x;
    static float target1 = 27;

    float hyp2 = y * y * y * x;
    static float target2 = 24;

    float hyp3 = x * y * z * z;
    static float target3 = 96;


    float error1 = fabs(hyp1 - target1);
    float error2 = fabs(hyp2 - target2);
    float error3 = fabs(hyp3 - target3);

    //indiv.setFitness(max(max(error1, error2), error3));
    indiv.setFitness(error1 + error2 + error3);
}
