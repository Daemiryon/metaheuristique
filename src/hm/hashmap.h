#ifndef _HASHMAP_
#define _HASHMAP_

#include "list.h"
#include "hash.h"

typedef struct _hashmap hashmap;

struct _hashmap
{
    int size;
    list **tbl;
};

hashmap *hm_create(int size);

void hm_destroy(hashmap *one_hm);

int hm_indexof(hashmap *one_hm, char *one_key);

bool hm_add(hashmap *one_hm, char *one_key, int one_value);

bool hm_contains(hashmap *one_hm, char *one_key);

int hm_get(hashmap *one_hm, char *one_key);

hashmap *dico_load(char *filename);

char *create_str(char *m);

#endif /* _HASHMAP_ */
