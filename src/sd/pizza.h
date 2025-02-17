#ifndef _PIZZA_
#define _PIZZA_

#include "clients.h"
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include "../io.h"

#define PIZZA_ENFANT_ALGO 1
// 0 -> triploide
// 1 -> classic diploide

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

void pizza_save_in_file(pizza *pz, input_data *data, const char *file_name);

void pizza_copy(pizza *pz_dest, pizza *pz_srce);

void pizza_enfant(pizza *pz_dest, pizza* pz1, pizza* pz2, pizza* pz3, int proba_mutation);

int pizza_next_pizza(pizza* pz);

void pizza_get_voisine(pizza *pz_dest, pizza *pz_srce);

#endif /* _PIZZA_ */