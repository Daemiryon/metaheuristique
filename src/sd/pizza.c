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

int pizza_note_pizza(pizza *pz, clients *clts)
{
    int c, lh_index, like, hate, res;
    res = 0;
    for (c = 0; c < clts->len; c++) // Pour chaque client
    {

        like = 0;
        for (lh_index = 0; lh_index < get_like_len(clts, c); lh_index++) // Pour chaque like
        {

            if (pz->ingr[get_like(clts, c, lh_index)])
            {
                like++;
            }
        }

        hate = 0;
        for (lh_index = 0; (lh_index < get_hate_len(clts, c) && !hate); lh_index++) // Pour chaque hate
        {
            if (pz->ingr[get_hate(clts, c, lh_index)])
            {
                hate = 1;
            }
        }

        printf("like %d, hate %d\n", like, hate);

        if (like == get_like_len(clts, c) && !hate)
            res++;
    }
    return res;
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
