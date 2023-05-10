#include "io.h"
#include "verbose.h"
#include "sd/pizza.h"
#include "sd/population.h"
#include "recuit.h"
#include "graph.h"

int main(int argc, char const *argv[])
{
    /******** ******** ********
    ****** ARGS PARSING *****
    ******** ******** ********/
    const char *file_name = NULL;
    const char *output = "last_try";
    int io_hm_size = 500;
    enum Algo_
    {
        Exp,
        Gen,
        Recuit
    };
    typedef enum Algo_ Algo;
    Algo algo = Gen;
    int fep = 1;
    int iterate = 1000;
    int target = -1;
    verbose = 0;
    graph = NULL;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--help") == 0)
        {
            printf("./main file_name {--help} {--io_hm_size arg} {--algo arg} {--output arg} {--fep arg} {--iterate arg} {--target arg} {--graph arg}\n");
            printf("\t--help        Affiche cette aide\n");
            printf("\t--io_hm_size  Paramètre la taille de la hashmap pour parser le fichier entrée\n");
            printf("\t              (0 < io_hm_size < 65536, valeur par défaut : %d)\n", io_hm_size);
            printf("\t--verbose     Affiche les étapes de l'exécution\n");
            printf("\t--algo        Paramètre l'algorithme d'IA utilisé\n");
            printf("\t              (doit être gen, exp ou recuit, valeur par défaut : gen)\n");
            printf("\t--output      Paramètre le fichier le sortie\n");
            printf("\t              (doit être un nom de fichier valide, valeur par défaut : `last_try`)\n");
            printf("\t--fep         Paramètre le nombre de threads à utiliser\n");
            printf("\t              (1 < fep < 128, valeur par défaut : %d)\n", fep);
            printf("\t--iterate     Paramètre le nombre d'itérations (gen)\n");
            printf("\t              (1 < iterate, valeur par défaut : %d)\n", iterate);
            printf("\t--target      Paramètre l'objectif à atteindre (gen et recuit)\n");
            printf("\t              (si -1 alors continue jusqu'à fin du recuit/nombre d'itérations, valeur par défaut : %d)\n", target);
            printf("\t--graph       Paramètre le fichier le sortie du graphe\n");
            printf("\t              (doit être un nom de fichier valide si NULL alors n'écrit pas, valeur par défaut : NULL)\n");
            return 0;
        }
        else if (strcmp(argv[i], "--verbose") == 0)
        {
            verbose = 1;
        }
        else if (strcmp(argv[i], "--fep") == 0)
        {
            if (i + 1 < argc)
            {
                fep = atoi(argv[i + 1]);
                if (fep < 1 || fep >= 128)
                {
                    printf("Argument invalide pour --fep (voir ./main --help)\n");
                    exit(1);
                }
                i++;
            }
            else
            {
                printf("Argument manquant pour --fep (voir ./main --help)\n");
                exit(1);
            }
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
        else if (strcmp(argv[i], "--iterate") == 0)
        {
            if (i + 1 < argc)
            {
                iterate = atoi(argv[i + 1]);
                if (iterate < 1)
                {
                    printf("Argument invalide pour --iterate (voir ./main --help)\n");
                    exit(1);
                }
                i++;
            }
            else
            {
                printf("Argument manquant pour --iterate (voir ./main --help)\n");
                exit(1);
            }
        }
        else if (strcmp(argv[i], "--target") == 0)
        {
            if (i + 1 < argc)
            {
                target = atoi(argv[i + 1]);
                if (iterate < -1)
                {
                    printf("Argument invalide pour --target (voir ./main --help)\n");
                    exit(1);
                }
                i++;
            }
            else
            {
                printf("Argument manquant pour --target (voir ./main --help)\n");
                exit(1);
            }
        }
        else if (strcmp(argv[i], "--algo") == 0)
        {
            if (i + 1 < argc)
            {
                if (strcmp(argv[i + 1], "gen") == 0)
                {
                    algo = Gen;
                }
                else if (strcmp(argv[i + 1], "recuit") == 0)
                {
                    algo = Recuit;
                }
                else if (strcmp(argv[i + 1], "exp") == 0)
                {
                    algo = Exp;
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
        else if (strcmp(argv[i], "--output") == 0)
        {
            if (i + 1 < argc)
            {
                output = argv[i+1];
                i++;
            }
            else
            {
                printf("Argument manquant pour --output (voir ./main --help)\n");
                exit(1);
            }
        }
        else if (strcmp(argv[i], "--graph") == 0)
        {
            if (i + 1 < argc)
            {
                graph = argv[i+1];
                i++;
            }
            else
            {
                printf("Argument manquant pour --graph (voir ./main --help)\n");
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
        if (algo == Gen)
        {
            printf("algo : gen\n");
            printf("fep : %d\n", fep);
            printf("iterate : %d\n", iterate);
            printf("target : %d\n", target);
        }
        else if (algo == Exp)
        {
            printf("algo : exp\n");
            printf("fep : unsupported for exp\n");
            printf("iterate : unsupported for exp\n");
            printf("target : unsupported for exp\n");
        }
        else
        {
            printf("algo : recuit\n");
            printf("fep : unsupported for recuit\n");
            printf("iterate : unsupported for recuit\n");
            printf("target : %d\n", target);
        }
        printf("output : %s\n", output);
        printf("graph : %s\n", graph);
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
    srand(time(NULL));
    graph_open();

    if (algo == Exp)
    {
        pizza *pz = pizza_create(data->nb_ingr);
        pizza *best_pz = pizza_create(data->nb_ingr);
        int note;
        int best_note = -1;
        int done = 0;
        while (pizza_next_pizza(pz))
        {
            note = pizza_note_pizza(pz, data->clts);
            if (note > best_note)
            {
                best_note = note;
                pizza_copy(best_pz, pz);
            }
            if (done++ == 0x1000) // 2^12
                verbose_estimated_long(12, data->nb_ingr);
        }

        printf("Meilleure note : %d.\n", best_note);
        pizza_print(best_pz, data);
        pizza_save_in_file(best_pz, data, output);

        pizza_destroy(pz);
        pizza_destroy(best_pz);
    }
    else if (algo == Gen)
    {
        verbose_section("CREATE A RANDOM POPULATION");
        population *pop = population_create(100, data->nb_ingr);
        population_compose_random(pop);

        verbose_section("EVALUATE POPULATION");
        int max_fit_index = 0;
        for (int i = 0; i < iterate && (target == -1 || pop->notes[max_fit_index] < target); i++)
        {
            if (i == 100)
                verbose_estimated(100, iterate);
            max_fit_index = population_note_pizzas(pop, data->clts, fep);
            population_nextgen(pop, max_fit_index, fep);
            graph_write_gen(i, pop->notes[max_fit_index]);
        }

        printf("Meilleure note après %d itérations : %d.\n", iterate, pop->notes[max_fit_index]);
        pizza_save_in_file(pop->pzs[max_fit_index], data, output);

        verbose_section("FREE PIZZA");
        population_destroy(pop);
    }
    else if (algo == Recuit)
    {
        pizza *pizza0 = pizza_create(data->nb_ingr);
        pizza *pizza_voisine = pizza_create(data->nb_ingr);
        pizza *pizza_swap;
        int score0, score_voisine, delta_E;
        double T = RECUIT_T_INIT;
        int nb_accept = 0;

        verbose_section("CREATE A RANDOM PIZZA");
        pizza_compose_random(pizza0);
        score0 = pizza_note_pizza(pizza0, data->clts);

        verbose_section("RECUIT RUNNING");
        if (verbose)
            printf("\n");
        while (T > RECUIT_T_LIM && (target == -1 || score0 < target))
        {
            for (int i = 0; i < 100; i++)
            {
                pizza_get_voisine(pizza_voisine, pizza0);
                score_voisine = pizza_note_pizza(pizza_voisine, data->clts);

                delta_E = score0 - score_voisine;

                if (metropolis_accept(delta_E, T))
                {
                    // Swap pizzas
                    pizza_swap = pizza0;
                    pizza0 = pizza_voisine;
                    pizza_voisine = pizza_swap;
                    // Update score
                    score0 = score_voisine;
                    // increase nb_accept
                    nb_accept++;
                }

                if (nb_accept == 12)
                    break;
            }
            graph_write_recuit(T, score0);
            if (verbose)
                printf("\33MScore : %d\n", score0);
            nb_accept = 0;
            T = RECUIT_T_GEO * T;
        }

        printf("Meilleure note : %d.\n", score0);
        pizza_save_in_file(pizza0, data, output);

        verbose_section("FREE PIZZA");
        pizza_destroy(pizza0);
        pizza_destroy(pizza_voisine);
    }

    verbose_time();
    graph_close();
    /******** ******** ********
    ******** FREE ********
    ******** ******** ********/
    input_data_destroy(data);
    return 0;
}
