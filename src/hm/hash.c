#include "hash.h"

/**
 * Il prend une chaîne et renvoie la somme des valeurs ASCII des caractères de la chaîne
 *
 * @param some_value La valeur à hacher.
 *
 * @return Somme des valeurs ASCII des caractères de la chaîne.
 */
int hash(char *some_value)
{
    int res = 0;
    int i = 0;

    for (i = 0; some_value[i] != '\0'; i++)
    {
        res = res + some_value[i];
    }
    return res;
}