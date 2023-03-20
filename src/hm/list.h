#ifndef _LIST_
#define _LIST_

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct _list_elemt
{
    char *key;
    int value;
};

typedef struct _list_elemt list_elemt;

struct _list
{
    list_elemt *head;
    struct _list *tail;
};

typedef struct _list list;

list *list_create();

void list_destroy(list *one_list);

bool list_is_empty(list *one_list);

void list_append(list *one_list, char *one_key, int one_value);

void element_print(list_elemt *one_element);

void list_print(list *one_list);

bool list_contains(list *one_list, char *one_key);

int list_find(list *one_list, char *one_key);

#endif /* _LIST_ */
