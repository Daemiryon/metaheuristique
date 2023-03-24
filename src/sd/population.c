#include "population.h"

population *population_create(int nb_pzs, int nb_ingr)
{
    population *res = malloc(sizeof(population));
    res->nb_pzs = nb_pzs;
    res->pzs = malloc(nb_pzs * sizeof(pizza *));
    res->pzs_backup = malloc(nb_pzs * sizeof(pizza *));
    res->notes = calloc(nb_pzs, sizeof(int));
    for (int i = 0; i < nb_pzs; i++)
    {
        res->pzs[i] = pizza_create(nb_ingr);
        res->pzs_backup[i] = pizza_create(nb_ingr);
    }
    res->proba_mutation = 2;
    return res;
}

void population_destroy(population *pop)
{
    for (int i = 0; i < pop->nb_pzs; i++)
    {
        pizza_destroy(pop->pzs[i]);
        pizza_destroy(pop->pzs_backup[i]);
    }
    free(pop->pzs);
    free(pop->pzs_backup);
    free(pop->notes);
    free(pop);
}

void population_compose_random(population *pop)
{
    for (int i = 0; i < pop->nb_pzs; i++)
        pizza_compose_random(pop->pzs[i]);
}

void population_note_pizzas(population *pop, clients *clts)
{
    for (int i = 0; i < pop->nb_pzs; i++)
        pop->notes[i] = pizza_note_pizza(pop->pzs[i], clts);
}

void population_nextgen(population *pop)
{
    pizza **pzs_srce = pop->pzs;
    pizza **pzs_dest = pop->pzs_backup;

    // TODO

    pop->nb_pzs = pzs_dest;
    pop->pzs_backup = pzs_srce;
}
