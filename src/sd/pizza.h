#ifndef _PIZZA_
#define _PIZZA_

#include "clients.h"
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include "../io.h"

struct pizza_
{
    bool *ingr;
    int nb_ingr;
};

typedef struct pizza_ pizza;

pizza *pizza_create(int nbr_ingr);
void pizza_destroy(pizza *pz);

void pizza_compose_random(pizza *pz);

int pizza_note_pizza(pizza *pz, clients *clts);

void pizza_print(pizza *pz, input_data *data);

void pizza_copy(pizza *pz_dest, pizza *pz_srce);

#endif /* _PIZZA_ */