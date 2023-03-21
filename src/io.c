#include "io.h"

/**
 * Il crée une structure input_data et renvoie un pointeur vers celle-ci
 *
 * @return Un pointeur vers une structure input_data.
 */
input_data *input_data_create()
{
    input_data *res = malloc(sizeof(input_data));
    res->parsed = false;
    return res;
}

/**
 * Il libère la mémoire allouée au input_data.
 *
 * @param data un pointeur vers le input_data
 */
void input_data_destroy(input_data *data)
{
    if (data->parsed)
    {
        for (int i = 1; i < data->nb_ingr; i++)
        {
            free(data->reversed_hm[i]);
        }
        hm_destroy(data->hm);
        free(data->reversed_hm);
        clients_destroy(data->clts);
    }
    free(data);
}

void lire_ingredient(input_data *data, int client_index, int ingre_index, char *ingre_str, int lh)
{
    int val = hm_get(data->hm, ingre_str);
    if (!val)
    {
        ingre_str = create_str(ingre_str);
        val = data->nb_ingr;
        data->nb_ingr++;
        hm_add(data->hm, ingre_str, val);
    }
    set_like_hate(data->clts, lh, client_index, ingre_index, val);
}

/**
 * Il parse le fichier d'entrée et en écrit le contenu dans data.
 *
 * @param input_data un pointeur vers le input_data
 * @param file_in nom du fichier à parser
 * @param io_hm_size la taille de la hashmap
 */
void io_parse(input_data *data, const char *file_in, int io_hm_size)
{
    FILE *fp;
    int c, n, i, j, lh;
    char mot[16];

    data->nb_ingr = 1;

    fp = fopen(file_in, "r");
    if (fp == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    fscanf(fp, "%d", &c);

    data->clts = clients_create(c);
    data->hm = hm_create(io_hm_size);

    for (i = 0; i < data->clts->len; i++)
    {
        for (lh = 0; lh <= 1; lh++)
        {
            fscanf(fp, "%d", &n);
            set_like_hate_len(data->clts, lh, i, n);
            for (j = 0; j < n; j++)
            {
                fscanf(fp, "%s", mot);
                lire_ingredient(data, i, j, mot, lh);
            }
        }
    }

    data->reversed_hm = calloc(data->nb_ingr, sizeof(char *));
    for (i = 0; i < data->hm->size; i++)
    {
        for (list *l = data->hm->tbl[i]; !list_is_empty(l); l = l->tail)
        {
            data->reversed_hm[l->head->value] = l->head->key;
        }
    }

    fclose(fp);
    data->parsed = true;
}