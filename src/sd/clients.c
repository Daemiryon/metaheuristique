#include "clients.h"

/**
 * Il alloue une structure clients, puis alloue un tableau d'entiers de longueur 10 * len
 *
 * @param len le nombre de clients
 *
 * @return Un pointeur vers une structure clients.
 */
clients *clients_create(int len)
{
    clients *res = malloc(sizeof(clients));
    res->len = len;
    res->array = calloc(len * 12, sizeof(int));
    return res;
}

/**
 * Il supprime la structure des clients de la mémoire
 *
 * @param clts La structure cliente.
 */
void clients_destroy(clients *clts)
{
    free(clts->array);
    free(clts);
}

/**
 * Il renvoie le nombre de likes pour un client donné
 *
 * @param clts la structure clients
 * @param i l'index du client
 *
 * @return La nombre de likes du client i
 */
int get_like_len(clients *clts, int i)
{
    return clts->array[i * 12];
}

/**
 * Il renvoie la valeur du tableau à l'index donné
 *
 * @param clts la structure clients
 * @param i l'index du client
 * @param j l'index du like
 *
 * @return La valeur du tableau à l'index i*10 + j.
 */
int get_like(clients *clts, int i, int j)
{
    return clts->array[i * 12 + j + 1];
}

/**
 * Il renvoie le nombre de hates pour un client donné
 *
 * @param clts la structure clients
 * @param i l'index du client
 *
 * @return La nombre de hates du client i
 */
int get_hate_len(clients *clts, int i)
{
    return clts->array[i * 12 + 6];
}

/**
 * Il renvoie la valeur du tableau à l'index donné
 *
 * @param clts la structure clients
 * @param i l'index du client
 * @param j l'index du hate
 *
 * @return La valeur du tableau à l'index i*10 + j.
 */
int get_hate(clients *clts, int i, int j)
{
    return clts->array[i * 12 + 6 + j + 1];
}

/**
 * Cette fonction définit le nombre de likes/hates pour un client donné
 *
 * @param clts la structure clients
 * @param lh 0 si like, 1 si hate
 * @param i le numéro de client
 * @param val la valeur à régler
 */
void set_like_hate_len(clients *clts, int lh, int i, int val)
{
    clts->array[i * 12 + 6 * lh] = val;
}

/**
 * Cette fonction définit la valeur du tableau à l'index donné
 *
 * @param clts la structure clients
 * @param lh 0 si like, 1 si hate
 * @param i le numéro de client
 * @param j l'index du like/hate
 * @param val la valeur à régler
 */
void set_like_hate(clients *clts, int lh, int i, int j, int val)
{
    clts->array[i * 12 + 6 * lh + j + 1] = val;
}