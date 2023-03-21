#include "hashmap.h"

/**
 * Il crée un hashmap avec une taille donnée et renvoie un pointeur vers celui-ci
 *
 * @param size la taille du hashmap
 *
 * @return Un pointeur vers une structure de hashmap.
 */
hashmap *hm_create(int size)
{
    hashmap *res = malloc(sizeof(hashmap));
    res->size = size;
    res->tbl = malloc(size * sizeof(list *));
    for (int i = 0; i < size; i++)
    {
        res->tbl[i] = list_create();
    }
    return res;
}

/**
 * Il libère la mémoire allouée au hashmap.
 *
 * @param one_hm un pointeur vers le hashmap
 */
void hm_destroy(hashmap *one_hm)
{
    for (int i = 0; i < one_hm->size; i++)
    {
        list_destroy(one_hm->tbl[i]);
    }
    free(one_hm->tbl);
    free(one_hm);
}

/**
 * Il prend une clé et renvoie l'index du compartiment où cette clé doit être stockée
 *
 * @param one_hm le hashmap que vous utilisez
 * @param one_key la clé à hacher
 *
 * @return L'index de la clé dans le hashmap.
 */
int hm_indexof(hashmap *one_hm, char *one_key)
{
    int i = hash(one_key) % one_hm->size;
    if (i < 0)
    {
        i = i + one_hm->size;
    }
    return i;
}

/**
 * > Si la clé n'est pas dans le hmau, ajoutez-la
 *
 * @param one_hm le hashmap que vous souhaitez ajouter à
 * @param one_key la clé à ajouter au hmau
 * @param one_value la valeur à ajouter au hmau
 *
 * @return Une valeur booléenne.
 */
bool hm_add(hashmap *one_hm, char *one_key, int one_value)
{
    int i = hm_indexof(one_hm, one_key);
    bool res = list_contains(one_hm->tbl[i], one_key);
    if (res)
    {
        return false;
    }
    else
    {
        list_append(one_hm->tbl[i], one_key, one_value);
        return true;
    }
}

/**
 * > Si la hm contient la clé, retourne vrai. Sinon, retourne faux
 *
 * @param one_hm le hashmap que vous souhaitez rechercher
 * @param one_key la clé pour chercher
 *
 * @return Une valeur booléenne.
 */
bool hm_contains(hashmap *one_hm, char *one_key)
{
    int i = hm_indexof(one_hm, one_key);
    return list_contains(one_hm->tbl[i], one_key);
}

/**
 * Il renvoie la valeur associée à la clé donnée
 *
 * @param one_hm le hashmap que vous souhaitez utiliser
 * @param one_key la clé pour chercher
 *
 * @return La valeur de la clé.
 */
int hm_get(hashmap *one_hm, char *one_key)
{
    int i = hm_indexof(one_hm, one_key);
    return list_find(one_hm->tbl[i], one_key);
}

/**
 * Il copie une chaîne dans un nouvel espace mémoire réservé.
 *
 * @param m Le message à envoyer.
 */
char *create_str(char *m)
{
    char *res = calloc(16, sizeof(char));
    strcpy(res, m);
    return res;
}
