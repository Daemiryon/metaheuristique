#ifndef _IO_
#define _IO_

#include <stdio.h>
#include <stdbool.h>
#include "hm/hashmap.h"
#include "sd/clients.h"

#define LINE_LEN 512 // 2 + 5*16 + 1 = 323 < 512

struct input_data_
{
    bool parsed;
    hashmap *hm;
    char **reversed_hm;
    clients *clts;
};

typedef struct input_data_ input_data;

input_data *input_data_create();
void input_data_destroy(input_data *data);

void io_parse(input_data* data, const char* file_in);

#endif /* _IO_ */
