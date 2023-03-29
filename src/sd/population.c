#include "population.h"
#include "math.h"

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

int population_note_pizzas(population *pop, clients *clts)
{
    int m = 0;
    for (int i = 0; i < pop->nb_pzs; i++)
    {
        pop->notes[i] = pizza_note_pizza(pop->pzs[i], clts);
        if (pop->notes[m] < pop->notes[i])
            m = i;
    }
    return m;
}

int roulette(int *notes, int len, int max_fit_index)
{
    int i, r, s, prob, note;
    double coeff = 30.0 / notes[max_fit_index];
    // Obtenir un nombre aléatoire
    r = random32();
    // Calculer la somme des notes
    s = 0;
    for (i = 0; i < len; i++)
    {
        note = (int)(notes[i] * coeff);

        prob = note * note;
        if (i == max_fit_index)
        {
            prob = prob * note;
        }

        s = s + prob;
    }
    if (s == 0)
        return r % len;
    // On prend r dans [0, s[
    r = r % s;
    // Boucle pour trouver l'indice
    for (i = 0; (r >= 0 && i < len); i++)
    {
        note = (int)(notes[i] * coeff);

        prob = note * note;
        if (i == max_fit_index)
        {
            prob = prob * note;
        }
        r = r - prob;
    }
    return i - 1;
}

void population_nextgen(population *pop, int max_fit_index)
{
    pizza **pzs_srce = pop->pzs;
    pizza **pzs_dest = pop->pzs_backup;

    for (int i = 0; i < pop->pzs[0]->nb_ingr; i++)
    {
        pzs_dest[0]->ingr[i] = pzs_srce[max_fit_index]->ingr[i];
    }

    for (int i = 1; i < pop->nb_pzs; i++)
    {
        pizza_enfant(
            pzs_dest[i],
            pzs_srce[roulette(pop->notes, pop->nb_pzs, max_fit_index)],
            pzs_srce[roulette(pop->notes, pop->nb_pzs, max_fit_index)],
            pzs_srce[roulette(pop->notes, pop->nb_pzs, max_fit_index)],
            pop->proba_mutation);
    }

    pop->pzs = pzs_dest;
    pop->pzs_backup = pzs_srce;
}
