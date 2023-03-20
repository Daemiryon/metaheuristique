#include "list.h"

/**
 * Créez une nouvelle liste et renvoyez-y un pointeur.
 *
 * @return Un pointeur vers une liste.
 */
list *list_create()
{
    list *res = malloc(sizeof(list));
    res->head = NULL;
    res->tail = 0;
    return res;
}

/**
 * Libérez la mémoire allouée à la liste, en commençant par la tête et en descendant jusqu'à la fin.
 *
 * @param one_list un pointeur vers la liste que vous voulez détruire
 */
void list_destroy(list *one_list)
{
    list *current = one_list;
    list *current_;
    while (!list_is_empty(current))
    {
        free(current->head);
        current_ = current->tail;
        free(current);
        current = current_;
    }
    free(current);
}

/**
 * Si le pointeur de queue est zéro, alors la liste est vide.
 *
 * @param one_list un pointeur vers la liste que vous voulez vérifier
 *
 * @return La queue de la liste.
 */
bool list_is_empty(list *one_list)
{
    return (one_list->tail == 0);
}

/**
 * Il prend une liste, une clé et une valeur, et renvoie une nouvelle liste avec la nouvelle paire
 * clé-valeur en tête de liste
 *
 * @param one_list un pointeur vers une liste
 * @param one_key la clé de l'élément à ajouter
 * @param one_value la valeur du nouvel élément
 */
void list_append(list *one_list, char *one_key, int one_value)
{
    list_elemt *h = malloc(sizeof(list_elemt));
    h->key = one_key;
    h->value = one_value;
    list *res = malloc(sizeof(list));
    res->head = one_list->head;
    res->tail = one_list->tail;
    one_list->head = h;
    one_list->tail = res;
}

/**
 * Il imprime la clé et la valeur d'un élément de liste
 *
 * @param one_element un pointeur vers l'élément à imprimer
 */
void element_print(list_elemt *one_element)
{
    printf("%s: %d", one_element->key, one_element->value);
}

/**
 * Imprime la liste.
 *
 * @param one_list un pointeur vers la liste à imprimer
 */
void list_print(list *one_list)
{
    printf("[");
    if (list_is_empty(one_list))
    {
        printf("]\n");
    }
    else
    {
        element_print(one_list->head);
        list *current = one_list->tail;
        while (!list_is_empty(current))
        {
            printf(", ");
            element_print(current->head);
            current = current->tail;
        }
        printf("]\n");
    }
}

/**
 * Si la liste est vide, retourne false ; sinon, parcourez la liste et retournez true si la clé est
 * trouvée, false sinon
 *
 * @param one_list la liste à rechercher
 * @param one_key la clé pour chercher
 *
 * @return Une valeur booléenne.
 */
bool list_contains(list *one_list, char *one_key)
{
    if (list_is_empty(one_list))
    {
        return false;
    }
    else
    {
        list *current = one_list;
        while (!list_is_empty(current))
        {
            if (strcmp(current->head->key, one_key) == 0)
            {
                return true;
            }
            current = current->tail;
        }
        return false;
    }
}

/**
 * Si la liste est vide, retournez NULL ; sinon, parcourez la liste jusqu'à ce que vous trouviez la clé
 * et renvoyez la valeur
 *
 * @param one_list la liste à rechercher
 * @param one_key la clé que vous cherchez
 *
 * @return La valeur de la clé.
 */
int list_find(list *one_list, char *one_key)
{
    if (list_is_empty(one_list))
    {
        return 0;
    }
    else
    {
        list *current = one_list;
        while (!list_is_empty(current))
        {
            if (strcmp(current->head->key, one_key) == 0)
            {
                return current->head->value;
            }
            current = current->tail;
        }
        return 0;
    }
}
