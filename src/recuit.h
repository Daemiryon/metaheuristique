#ifndef _RECUIT_
#define _RECUIT_

#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "sd/pizza.h"

#define RECUIT_T_INIT 2000.
#define RECUIT_T_LIM 0.0000000001
#define RECUIT_T_GEO 0.999
#define RECUIT_NB_ACCEPT 12

bool metropolis_accept(int delta_E, double T);

#endif /* _RECUIT_ */
