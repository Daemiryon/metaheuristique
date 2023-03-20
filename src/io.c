#include "io.h"

/**
 * Il crée une structure input_data et renvoie un pointeur vers celle-ci
 * 
 * @return Un pointeur vers une structure input_data.
 */
input_data* input_data_create() {
    input_data* res = malloc(sizeof(input_data));
    res->parsed = false;
    return res;
}

/**
 * Il libère la mémoire allouée au input_data.
 *
 * @param data un pointeur vers le input_data
 */
void input_data_destroy(input_data* data) {
    if (data->parsed) {
        hm_destroy(data->hm);
        free(data->reversed_hm);
        clients_destroy(data->clts);
    }
    free(data);
}

/**
 * Il parse le fichier d'entrée et en écrit le contenu dans data.
 *
 * @param input_data un pointeur vers le input_data
 * @param file_in nom du fichier à parser
 */
void io_parse(input_data* data, const char* file_in) {
    FILE* fd = fopen(file_in, "r");

    // TODO

    fclose(fd);
}