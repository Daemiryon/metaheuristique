#include "pizza.h"

pizza *pizza_create(int nbr_ingr)
{
    pizza *res = calloc(1, sizeof(pizza));
    res->nb_ingr = nbr_ingr;
    res->ingr = calloc(nbr_ingr, sizeof(bool));
    return res;
}

void pizza_destroy(pizza *pz)
{
    free(pz->ingr);
    free(pz);
}

void pizza_compose_random(pizza *pz)
{
    int i, j, r;
    i = 1;
    srand(time(NULL));
    while (i < pz->nb_ingr)
    {
        r = rand();
        for (j = 0; (i < pz->nb_ingr && j < 30); j++)
        {
            pz->ingr[i] = r % 2;
            i++;
            r = r / 2;
        }
    }
}

pizza_note *pizza_note_create()
{
    return calloc(1, sizeof(pizza_note));
}

void pizza_note_destroy(pizza_note *pz_note)
{
    free(pz_note);
}

void pizza_note_pizza(pizza *pz, pizza_note *pz_note, clients *clts)
{
    int c, lh_index, i, skip;
    pz_note->nb_likes = 0;
    pz_note->nb_hates = 0;
    for (i = 1; i < pz->nb_ingr; i++) // Pour chaque ingrédient
    {

        skip = 0;
        for (c = 0; (c < clts->len && !skip); c++) // Pour chaque client
        {
            for (lh_index = 0; lh_index < get_like_len(clts, c); lh_index++) // Pour chaque like
            {
                if (get_like(clts, c, lh_index) == pz->ingr[i])
                {
                    pz_note->nb_likes++;
                    skip = 1;
                }
            }
        }
        skip = 0;
        for (c = 0; (c < clts->len && !skip); c++) // Pour chaque client
        {
            for (lh_index = 0; lh_index < get_hate_len(clts, c); lh_index++) // Pour chaque hate
            {
                if (get_hate(clts, c, lh_index) == pz->ingr[i])
                {
                    pz_note->nb_hates++;
                    skip = 1;
                }
            }
        }
    }
}

void pizza_print(pizza *pz, input_data *data)
{
    int i, n;
    n = 0;
    for (i = 1; i < pz->nb_ingr; i++)
    {
        if (pz->ingr[i])
            n++;
    }
    printf("%d ", n);
    for (i = 1; i < pz->nb_ingr; i++)
    {
        if (pz->ingr[i])
            printf("%s ", data->reversed_hm[i]);
    }
    printf("\n");
}
