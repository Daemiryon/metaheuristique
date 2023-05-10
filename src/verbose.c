#include "verbose.h"

int verbose;

int verbose_initialized = 0;
clock_t verbose_start_cpu_time;
time_t verbose_start_wall_time;
clock_t verbose_last_cpu_time;
time_t verbose_last_wall_time;

void verbose_section(const char *section_name)
{
    if (verbose)
    {
        verbose_time();
        printf("=== %s ===\n", section_name);
    }
}

void verbose_time()
{
    if (verbose)
    {
        clock_t cpu_time = clock();
        time_t wall_time = time(NULL);
        if (!verbose_initialized)
        {
            verbose_initialized = 1;
            verbose_start_cpu_time = cpu_time;
            verbose_start_wall_time = wall_time;
            printf("\033[1;35m[pid:%d] %s\033[0m", getpid(), ctime(&verbose_start_wall_time));
        }
        else
        {
            printf("\033[1;35mTemps (tâche) : %8ld secondes [CPU: %8ld]\033[0m\n",
                   (long)(wall_time - verbose_last_wall_time),
                   (long)(cpu_time - verbose_last_cpu_time));
            printf("\033[1;35mTemps (total) : %8ld secondes [CPU: %8ld]\033[0m\n",
                   (long)(wall_time - verbose_start_wall_time),
                   (long)(cpu_time - verbose_start_cpu_time));
        }
        verbose_last_cpu_time = cpu_time;
        verbose_last_wall_time = wall_time;
    }
}

void verbose_estimated(int nb_done, int nb_tot_todo)
{
    if (verbose)
    {
        long int restant = (time(NULL) - verbose_start_wall_time) * nb_tot_todo / nb_done;
        printf("Temps de calcul estimé : %ldh %ldm %lds.\n",
               restant / 3600,
               (restant / 60) % 60,
               restant % 60);
    }
}

void verbose_estimated_long(int log2_nb_done, int log2_nb_tot_todo)
{
    if (verbose)
    {
        long int spent = time(NULL) - verbose_start_wall_time;
        float f = (float)spent;
        f = f / 31557600 * 1000000000.; // nombre de secondes par an *10^9
        if (f < 0.00001)
            f = 0.00001;
        printf("Temps de calcul estimé : %f * 10^%d ans.\n",
               f,
               (log2_nb_tot_todo - log2_nb_done) * 3 / 10 + 9);
    }
}
