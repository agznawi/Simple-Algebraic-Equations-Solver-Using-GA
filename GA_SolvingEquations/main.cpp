#include "individual.h"
#include "population.h"
#include "evolution.h"

#include <fstream>
using std::ifstream;
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <iomanip>
using std::setw;
using std::left;
#include <math.h>
//pow()
#include <random>
using std::random_device;
using std::default_random_engine;
using std::uniform_int_distribution;
using std::uniform_real_distribution;


random_device r;
default_random_engine e1(r());

int Individual::variableRange = 10000; //
const int floatPrecesion = 0; // Number of floating points in each variable
int Evolution::divPrecesion = pow(10, floatPrecesion); //
int Evolution::maxMutationSize = 1000; //

void printPopulation(Population pop, int count);

int main()
{
    // Evolution values
    const int POP_SIZE = 100000; // Population size
    const float MUTATION_THRESHOLD = 0.01f; // Mutation rate of individuals
    const float SURVIVAL_RATE = 0.5f; // Survival rate, ratio of best individuals that will possibily breed
    const bool ELITISM = false; // Using elitism
    const float ELITISM_RATIO = 0.000001f; // Elitism ratio

    // Display values
    const int dispIndivs = 1; // Number of individuals to be displayed
    const bool skip = false; // Using 'return' key to evolve to next generation
    const int skipGenerations = 1; // Number of generations to be skipped before displaying

    // Algorithm values
    const unsigned survived = SURVIVAL_RATE * POP_SIZE; // Number of survived individuals
    const unsigned elite = (ELITISM)? ELITISM_RATIO * POP_SIZE : 0; // Number of elite individuals

    // Make sure values are valid
    /// assert survived;
    /// assert mutationThreshold;
    /// assert maxElitism;


    // Initialize generation 0
    Population pop(POP_SIZE); // Create random population
    for(int i = 0; i < POP_SIZE; i++) // Calculate population fitness
        Evolution::calculateFitness(pop.individuals.at(i));
    pop.sortByFitness(); // Sort population by fitness

    system("clear"); // Yeah whatever
    cout << "Generation: 0 | ";
    printPopulation(pop, dispIndivs); // Output
    if(skip) getchar();

    // Produce and evolve generations forever or until the perfect solution appears
    for(int generation = 1;; generation++)
    {
        vector<Individual> newPopulation;

        // Elitism
        if(ELITISM)
            for(unsigned i = 0; i < elite; i++)
                newPopulation.push_back(pop.individuals.at(i));

        // Create new child individuals, mutate and calculate their fitnesses
        for(int i = elite; i < POP_SIZE; i++)
        {
            uniform_int_distribution<int> rSelect(0, survived);
            int indivIndex1 = rSelect(e1);
            int indivIndex2 = rSelect(e1);

            // Crossover
            // Create new Individual
            Individual indiv(Evolution::crossover(pop.getIndividual(indivIndex1), pop.getIndividual(indivIndex2)));

            // Expose Individual to mutation
            uniform_real_distribution<float> rMut(0, 1);
            if(rMut(e1) < MUTATION_THRESHOLD) // If rMut() is below mutation threshold:
                Evolution::mutate(indiv); // Individual will mutate

            // Calculate Individual fitness
            Evolution::calculateFitness(indiv);

            // Add Individual to the new population
            newPopulation.push_back(indiv);
        }

        pop.individuals = newPopulation; // Replace population
        pop.sortByFitness(); // Sort population by fitness

        if(!(generation % skipGenerations))
        {
            system("clear");
            cout << "Generation: " << generation << " | ";
            printPopulation(pop, dispIndivs);
            cout.flush();
            if(skip) getchar();
        }

        if(pop.getIndividual(0).getFitness() == 0)
        {
            cout << "Found the perfect solution!\n";
            system("clear");
            cout << "Generation: " << generation << " | ";
            printPopulation(pop, dispIndivs);
            break;
        }
    }

    return 0;
}

void printPopulation(Population pop, int count)
{
    static int divPre = Evolution::divPrecesion;
    int popSize = pop.getPopulationCount();
    float avg = 0;
    for(int i = 0; i < popSize; i++)
        avg += pop.getIndividual(i).getFitness();
    avg /= popSize;

    cout << "Solving for: X^3 = 27, Y^3 * X = 24, X * Y * Z^2 = 96\n";
    cout << "Best fit = " << pop.getIndividual(0).getFitness() <<
            " | Worst fit = " << pop.getIndividual(popSize-1).getFitness() <<
            " | Avg fit = " << avg << endl;

    for(int i = 0; i < count; i++)
    {
        cout << "Indiv" << left << setw(2) << i << " fitness = " << pop.getIndividual(i).getFitness() <<
                " for solution: ";
        for(int j = 0; j < Individual::numVariables; j++)
        {
            cout << pop.getIndividual(i).variables[j] / divPre << ' ';
        }
        cout << endl;
    }
}
