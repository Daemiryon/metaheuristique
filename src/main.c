#include "io.h"
#include "verbose.h"
#include "sd/pizza.h"
#include "sd/population.h"

int main(int argc, char const *argv[])
{
    /******** ******** ********
    ****** ARRGS PARSING *****
    ******** ******** ********/
    const char *file_name = NULL;
    int io_hm_size = 500;
    int algo = 1;
    verbose = 0;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--help") == 0)
        {
            printf("./main file_name {--help} {--io_hm_size arg} {--algo arg}\n");
            printf("\t--help Affiche cette aide\n");
            printf("\t--io_hm_size Paramètre la taille de la hashmap pour parser le fichier entrée\n");
            printf("\t (0 < io_hm_size < 65536, valeur par défaut : 500)\n");
            printf("\t--verbose Affiche les étapes de l'exécution\n");
            printf("\t--algo Paramètre l'algorithme d'IA utilisé\n");
            printf("\t (doit être gen ou tabou, valeur par défaut : gen)\n");
            return 0;
        }
        else if (strcmp(argv[i], "--verbose") == 0)
        {
            verbose = 1;
        }
        else if (strcmp(argv[i], "--io_hm_size") == 0)
        {
            if (i + 1 < argc)
            {
                io_hm_size = atoi(argv[i + 1]);
                if (io_hm_size < 0 || io_hm_size >= 65536)
                {
                    printf("Argument invalide pour --io_hm_size (voir ./main --help)\n");
                    exit(1);
                }
                i++;
            }
            else
            {
                printf("Argument manquant pour --io_hm_size (voir ./main --help)\n");
                exit(1);
            }
        }
        else if (strcmp(argv[i], "--algo") == 0)
        {
            if (i + 1 < argc)
            {
                if (strcmp(argv[i + 1], "gen") == 0)
                {
                    algo = 1;
                }
                else if (strcmp(argv[i + 1], "tabou") == 0)
                {
                    algo = 0;
                }
                else
                {
                    printf("Argument invalide pour --algo (voir ./main --help)\n");
                    exit(1);
                }
                i++;
            }
            else
            {
                printf("Argument manquant pour --algo (voir ./main --help)\n");
                exit(1);
            }
        }
        else
        {
            if (file_name == NULL)
            {
                file_name = argv[i];
            }
            else
            {
                printf("Trop d'arguments (voir ./main --help)\n");
                exit(1);
            }
        }
    }

    if (file_name == NULL)
    {
        printf("Nom de fichier manquant (voir ./main --help)\n");
        exit(1);
    }

    verbose_section("PARSING ARGS");
    if (verbose)
    {
        printf("io_hm_size : %d\n", io_hm_size);
        printf("verbose : true\n");
        if (algo)
            printf("algo : gen\n");
        else
            printf("algo : tabou\n");
    }

    /******** ******** ********
    ******** IO/ IN ********
    ******** ******** ********/
    verbose_section("PARSING FILE");
    input_data *data = input_data_create();
    io_parse(data, file_name, io_hm_size);

    /******** ******** ********
    ******** TODO ********
    ******** ******** ********/

    // Bonjour, je suis le code
    verbose_section("CREATE A RANDOM POPULATION");
    population* pop = population_create(1000, data->nb_ingr);

    verbose_section("EVALUATE POPULATION");
    population_note_pizzas(pop, data->clts);

    verbose_section("FREE PIZZA");
    population_destroy(pop);

    verbose_time();
    /******** ******** ********
    ******** FREE ********
    ******** ******** ********/
    input_data_destroy(data);
    return 0;
}
