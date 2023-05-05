#include "recuit.h"

bool metropolis_accept(int delta_E, double T)
{
    double r = ((double)rand()/(double)RAND_MAX); // Génération d'un nombre aléatoire entre 0 et 1
    return (delta_E <= 0) || (r < exp(-delta_E/T));
}
