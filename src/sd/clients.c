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
    res->array = malloc(len * 10 * sizeof(int));
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
    return clts->array[i * 10 + j];
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
    return clts->array[i * 10 + 5 + j];
}

/**
 * Cette fonction définit la valeur du tableau à l'index donné
 *
 * @param clts la structure clients
 * @param i le numéro de client
 * @param j l'index du like
 * @param val la valeur à régler
 */
void set_like(clients *clts, int i, int j, int val)
{
    clts->array[i * 10 + j] = val;
}

/**
 * Cette fonction définit la valeur du tableau à l'index donné
 *
 * @param clts la structure clients
 * @param i le numéro de client
 * @param j l'index du hate
 * @param val la valeur à régler
 */
void set_hate(clients *clts, int i, int j, int val)
{
    clts->array[i * 10 + 5 + j] = val;
}