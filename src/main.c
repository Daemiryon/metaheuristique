#include "io.h"

int main(int argc, char const *argv[])
{
    /******** ******** ********
     ****** ARRGS PARSING *****
     ******** ******** ********/
    const char *file_in;
    if (argc < 2)
    {
        printf("Usage : ./main file_name\n");
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
     ********   TODO   ********
     ******** ******** ********/

    // Bonjour, je suis le code
    
    /******** ******** ********
     ********   FREE   ********
     ******** ******** ********/
    input_data_destroy(data);
    return 0;
}
