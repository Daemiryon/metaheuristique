#ifndef _CLIENTS_
#define _CLIENTS_

#include <stdlib.h>

typedef int **client;

struct clients_
{
    int len;
    int *array;
    /*
     * Array est définit comme un tableau 3d géré par les fonctions (get|set)_(like|hate).
     * Dimension 1 : les clients (taille len)
     * Dimension 2 : like (0) ou hate (1)
     * Dimension 3 : l'ingrédient (ou 0 si absent)
     */
};

typedef struct clients_ clients;

clients *clients_create(int len);
void clients_destroy(clients *clts);

int get_like_len(clients *clts, int i);
int get_like(clients *clts, int i, int j);
int get_hate_len(clients *clts, int i);
int get_hate(clients *clts, int i, int j);

void set_like_hate_len(clients *clts, int lh, int i, int val);
void set_like_hate(clients *clts, int lh, int i, int j, int val);

#endif /* _CLIENTS_ */