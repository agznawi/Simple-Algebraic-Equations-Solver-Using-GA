#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <string>
using std::string;

class Individual
{
private:
    float fitness;

public:
    static const int numVariables = 3;
    static int variableRange;
    float variables[numVariables];

    Individual();
    Individual(float variables[numVariables]);
    void randomize();
    float getFitness();
    void setFitness(float f);
};

#endif // INDIVIDUAL_H
