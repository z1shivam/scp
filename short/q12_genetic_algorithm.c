// Q12.  Write a program in C to maximize F(X) = X^2 using Genetic Algorithm where 0<X<31.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define POPULATION_SIZE 10
#define MAX_GENERATIONS 50
#define MUTATION_RATE 0.1
#define CROSSOVER_RATE 0.7
#define CHROMOSOME_SIZE 5
#define TOURNAMENT_SIZE 3

typedef struct {
    int chromosome[CHROMOSOME_SIZE];
    int decoded_value;
    double fitness;
} Individual;

void initialize_population(Individual[]);
void evaluate_fitness(Individual*);
int binary_to_decimal(int[]);
void select_parents(Individual[], Individual*, Individual*);
void crossover(Individual*, Individual*, Individual*, Individual*);
void mutate(Individual*);
void copy_individual(Individual*, Individual*);
Individual find_best_individual(Individual[]);

int main() {
    srand(time(NULL));
    Individual population[POPULATION_SIZE];
    initialize_population(population);
    Individual best = find_best_individual(population);

    for (int generation = 0; generation < MAX_GENERATIONS; generation++) {
        Individual new_population[POPULATION_SIZE];
        copy_individual(&best, &new_population[0]);
        for (int i = 1; i < POPULATION_SIZE; i += 2) {
            Individual parent1, parent2, offspring1, offspring2;
            select_parents(population, &parent1, &parent2);
            if ((double)rand() / RAND_MAX < CROSSOVER_RATE)
                crossover(&parent1, &parent2, &offspring1, &offspring2);
            else {
                copy_individual(&parent1, &offspring1);
                copy_individual(&parent2, &offspring2);
            }
            mutate(&offspring1);
            mutate(&offspring2);
            copy_individual(&offspring1, &new_population[i]);
            if (i + 1 < POPULATION_SIZE)
                copy_individual(&offspring2, &new_population[i + 1]);
        }
        for (int i = 0; i < POPULATION_SIZE; i++)
            copy_individual(&new_population[i], &population[i]);
        best = find_best_individual(population);
    }

    printf("FINAL SOLUTION: X=%d, F(X)=%.0f\n", best.decoded_value, best.fitness);
    return 0;
}

void initialize_population(Individual population[]) {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        for (int j = 0; j < CHROMOSOME_SIZE; j++)
            population[i].chromosome[j] = rand() % 2;
        evaluate_fitness(&population[i]);
    }
}

void evaluate_fitness(Individual *individual) {
    individual->decoded_value = binary_to_decimal(individual->chromosome);
    individual->fitness = (double)(individual->decoded_value * individual->decoded_value);
}

int binary_to_decimal(int binary[]) {
    int decimal = 0;
    for (int i = 0; i < CHROMOSOME_SIZE; i++)
        decimal += binary[i] * (1 << (CHROMOSOME_SIZE - 1 - i));
    return decimal;
}

void select_parents(Individual population[], Individual *parent1, Individual *parent2) {
    int best_index = rand() % POPULATION_SIZE;
    for (int i = 1; i < TOURNAMENT_SIZE; i++) {
        int candidate = rand() % POPULATION_SIZE;
        if (population[candidate].fitness > population[best_index].fitness)
            best_index = candidate;
    }
    copy_individual(&population[best_index], parent1);
    int second_best_index;
    do {
        second_best_index = rand() % POPULATION_SIZE;
        for (int i = 1; i < TOURNAMENT_SIZE; i++) {
            int candidate = rand() % POPULATION_SIZE;
            if (population[candidate].fitness > population[second_best_index].fitness)
                second_best_index = candidate;
        }
    } while (second_best_index == best_index && POPULATION_SIZE > 1);
    copy_individual(&population[second_best_index], parent2);
}

void crossover(Individual *parent1, Individual *parent2, Individual *offspring1, Individual *offspring2) {
    int point = rand() % CHROMOSOME_SIZE;
    for (int i = 0; i < CHROMOSOME_SIZE; i++) {
        offspring1->chromosome[i] = i < point ? parent1->chromosome[i] : parent2->chromosome[i];
        offspring2->chromosome[i] = i < point ? parent2->chromosome[i] : parent1->chromosome[i];
    }
    evaluate_fitness(offspring1);
    evaluate_fitness(offspring2);
}

void mutate(Individual *individual) {
    for (int i = 0; i < CHROMOSOME_SIZE; i++)
        if ((double)rand() / RAND_MAX < MUTATION_RATE)
            individual->chromosome[i] = 1 - individual->chromosome[i];
    evaluate_fitness(individual);
}

void copy_individual(Individual *source, Individual *destination) {
    for (int i = 0; i < CHROMOSOME_SIZE; i++)
        destination->chromosome[i] = source->chromosome[i];
    destination->decoded_value = source->decoded_value;
    destination->fitness = source->fitness;
}

Individual find_best_individual(Individual population[]) {
    int best_index = 0;
    for (int i = 1; i < POPULATION_SIZE; i++)
        if (population[i].fitness > population[best_index].fitness)
            best_index = i;
    return population[best_index];
}