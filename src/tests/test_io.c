#include "../io.h"
#include "test.h"

int main(int argc, char const *argv[])
{
    /******** ******** ********
     ****** ARRGS PARSING *****
     ******** ******** ********/
    const char *file_in;
    if (argc < 2)
    {
        printf("Usage : ./test_io file_name\n");
        return 1;
    }
    else
    {
        file_in = argv[1];
    }

    /******** ******** ********
     ********  IO/ IN  ********
     ******** ******** ********/
    input_data *data = input_data_create();
    io_parse(data, file_in);

    /******** ******** ********
     ********   TEST   ********
     ******** ******** ********/
    printf(TEST_START, "IO");

    // On va juste imprimer ce qu'on a parsé !
    printf("CLIENTS : %d\n", data->clts->len);

    for (int i = 0; i < data->clts->len; i++)
    {
        printf("|\tClient #%d\n", i + 1);
        printf("|\t|\tLIKES : %d\n", get_like_len(data->clts, i));
        for (int j = 0; j < get_like_len(data->clts, i); j++)
        {
            printf("|\t|\t|\t%5d: %16p -> %16s\n", get_like(data->clts, i, j), data->reversed_hm[get_like(data->clts, i, j)], data->reversed_hm[get_like(data->clts, i, j)]);
        }
        printf("|\t|\tHATES : %d\n", get_hate_len(data->clts, i));
        for (int j = 0; j < get_hate_len(data->clts, i); j++)
        {
            printf("|\t|\t|\t%5d: %16p -> %16s\n", get_hate(data->clts, i, j), data->reversed_hm[get_hate(data->clts, i, j)], data->reversed_hm[get_hate(data->clts, i, j)]);
        }
    }

    printf("\nINGREDIENTS : %d\n", data->nb_ingr - 1);
    for (int i = 1; i < data->nb_ingr; i++)
    {
        printf("|\t%5d: %16s\n", i, data->reversed_hm[i]);
    }

    int maxi = -1;
    for (int i = 0; i < data->hm->size; i++)
    {
        int n = 0;
        for (list *l = data->hm->tbl[i]; !list_is_empty(l); l = l->tail)
        {
            n++;
        }
        if (n > maxi)
            maxi = n;
    }
    printf("\nUTILISATION DE LA HASHMAP : MAX=%d\n{", maxi);
    int n = -1;
    for (int i = 0; i < data->hm->size; i++)
    {
        if (n != -1)
            printf(", ");
        n = 0;
        for (list *l = data->hm->tbl[i]; !list_is_empty(l); l = l->tail)
        {
            n++;
        }
        printf("%d: %d", i, n);
    }
    printf("}\n");

    printf(TEST_END, "IO");
    /******** ******** ********
     ********   FREE   ********
     ******** ******** ********/
    input_data_destroy(data);
    return 0;
}
