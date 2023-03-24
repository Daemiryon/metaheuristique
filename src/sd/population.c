#include "population.h"

population* population_create(int nb_pzs, int nb_ingr){
    population* res = malloc(sizeof(population));
    res->nb_pzs = nb_pzs;
    res->pzs = malloc(nb_pzs * sizeof(pizza*));
    res->notes = calloc(nb_pzs, sizeof(int));
    for (int i = 0; i < nb_pzs; i++)
        res->pzs[i] = pizza_create(nb_ingr);
    return res;
}

void population_destroy(population* pop){
    for (int i = 0; i < pop->nb_pzs; i++)
        pizza_destroy(pop->pzs[i]);
    free(pop->pzs);
    free(pop->notes);
    free(pop);
}

void population_compose_random(population *pop) {
    for (int i = 0; i < pop->nb_pzs; i++)
        pizza_compose_random(pop->pzs[i]);
}

void population_note_pizzas(population* pop, clients *clts) {
    for (int i = 0; i < pop->nb_pzs; i++)
        pop->notes[i] = pizza_note_pizza(pop->pzs[i], clts);
}