#include "random.h"

int random32()
{
    srand(clock());
    return rand();
}
