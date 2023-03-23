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

struct pizza_note_
{
    int nb_likes;
    int nb_hates;
};

typedef struct pizza_note_ pizza_note;

pizza *pizza_create(int nbr_ingr);
void pizza_destroy(pizza *pz);

void pizza_compose_random(pizza *pz);

pizza_note *pizza_note_create();
void pizza_note_destroy(pizza_note *pz_note);

void pizza_note_pizza(pizza *pz, pizza_note *pz_note, clients *clts);

void pizza_print(pizza *pz, input_data *data);

#endif /* _PIZZA_ */