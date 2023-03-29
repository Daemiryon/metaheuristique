#ifndef _POPULATION_
#define _POPULATION_

#include "pizza.h"
#include <stdlib.h>
#include "../functions/random.h"

struct population_
{
    pizza **pzs;
    int nb_pzs;
    int *notes;
    int proba_mutation;
    pizza **pzs_backup;
};

typedef struct population_ population;

population *population_create(int nb_pzs, int nb_ingr);
void population_destroy(population *pop);

void population_compose_random(population *pop);

int population_note_pizzas(population *pop, clients *clts);

void population_nextgen(population *pop, int max_fit_index);

#endif /* _POPULATION_ */