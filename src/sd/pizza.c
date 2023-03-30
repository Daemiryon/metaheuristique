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
    while (i < pz->nb_ingr)
    {
        r = rand();
        for (j = 0; (i < pz->nb_ingr && j < 31 /*log2(2^31)*/); j++)
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

        like = 1;                                                                  // Optimisation de 25%
        for (lh_index = 0; (lh_index < get_like_len(clts, c) && like); lh_index++) // Pour chaque like
        {

            if (!pz->ingr[get_like(clts, c, lh_index)])
            {
                like = 0;
            }
        }

        hate = 0;                                                                   // Optimisation de 25%
        for (lh_index = 0; (lh_index < get_hate_len(clts, c) && !hate); lh_index++) // Pour chaque hate
        {
            if (pz->ingr[get_hate(clts, c, lh_index)])
            {
                hate = 1;
            }
        }

        if (like && !hate)
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

void pizza_save_in_file(pizza *pz, input_data *data, const char *file_name)
{
    FILE *fd = fopen(file_name, "w");
    int i, n, k;
    n = 0;
    char buf[20];
    for (i = 1; i < pz->nb_ingr; i++)
    {
        if (pz->ingr[i])
            n++;
    }
    k = sprintf(buf, "%d ", n);
    fwrite(buf, sizeof(char), k, fd);
    for (i = 1; i < pz->nb_ingr; i++)
    {
        if (pz->ingr[i])
        {
            k = sprintf(buf, "%s ", data->reversed_hm[i]);
            fwrite(buf, sizeof(char), k, fd);
        }
    }
    fclose(fd);
}

void pizza_copy(pizza *pz_dest, pizza *pz_srce)
{
    for (int i = 0; i < pz_dest->nb_ingr; i++)
        pz_dest->ingr[i] = pz_srce->ingr[i];
}

void pizza_enfant(pizza *pz_dest, pizza *pz1, pizza *pz2, pizza *pz3, int proba_mutation)
{
    if (rand() % proba_mutation != 0)
    {
        pizza_compose_random(pz_dest);
    }
    else
    {
        /*for (int i = 0; i < pz1->nb_ingr; i++)
        {
            pz_dest->ingr[i] = (
                (
                    pz1->ingr[i] && pz2->ingr[i]
                ) || (
                    pz2->ingr[i] && pz3->ingr[i]
                ) || (
                    pz3->ingr[i] && pz1->ingr[i]
                )
            );
        }*/
        pizza *tbl[] = {pz1, pz2, pz3};
        for (int i = 0; i < pz1->nb_ingr; i++)
        {
            pz_dest->ingr[i] = tbl[rand() % 3]->ingr[i];
        }
    }
}
