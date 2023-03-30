#include "population.h"
#include "math.h"

population *population_create(int nb_pzs, int nb_ingr)
{
    population *res = malloc(sizeof(population));
    res->nb_pzs = nb_pzs;
    res->pzs = malloc(nb_pzs * sizeof(pizza *));
    res->pzs_backup = malloc(nb_pzs * sizeof(pizza *));
    res->notes = calloc(nb_pzs, sizeof(int));
    res->notes_sum = -1;
    res->max_fit_index = -1;
    for (int i = 0; i < nb_pzs; i++)
    {
        res->pzs[i] = pizza_create(nb_ingr);
        res->pzs_backup[i] = pizza_create(nb_ingr);
    }
    res->proba_mutation = 2;
    return res;
}

void population_destroy(population *pop)
{
    for (int i = 0; i < pop->nb_pzs; i++)
    {
        pizza_destroy(pop->pzs[i]);
        pizza_destroy(pop->pzs_backup[i]);
    }
    free(pop->pzs);
    free(pop->pzs_backup);
    free(pop->notes);
    free(pop);
}

void population_compose_random(population *pop)
{
    for (int i = 0; i < pop->nb_pzs; i++)
        pizza_compose_random(pop->pzs[i]);
}

int population_note_pizzas_classic(population *pop, clients *clts)
{
    int m = 0;
    for (int i = 0; i < pop->nb_pzs; i++)
    {
        pop->notes[i] = pizza_note_pizza(pop->pzs[i], clts);
        if (pop->notes[m] < pop->notes[i])
            m = i;
    }
    pop->max_fit_index = m;
    return m;
}

struct FEP_note_pizza
{
    int id;
    int *m;
    int deb;
    int fin;
    population *pop;
    clients *clts;
    sem_t *sem;
};

void *fep_note_pizza(void *arg)
{
    struct FEP_note_pizza *a = (struct FEP_note_pizza *)arg;
    int i_local;
    int m_local = a->deb;

    for (i_local = a->deb; i_local < a->fin; i_local++)
    {
        a->pop->notes[i_local] = pizza_note_pizza(a->pop->pzs[i_local], a->clts);
        if (a->pop->notes[m_local] < a->pop->notes[i_local])
            m_local = i_local;
    }

    sem_wait(a->sem);
    if (a->pop->notes[m_local] > a->pop->notes[*(a->m)])
        *(a->m) = m_local;
    sem_post(a->sem);

    pthread_exit(NULL);
}

int population_note_pizzas_fep(population *pop, clients *clts, int fep)
{
    int m = 0;

    int calcul_par_thread = pop->nb_pzs / fep;

    sem_t sem;
    sem_init(&sem, 0, 1);

    pthread_t thread[fep];
    struct FEP_note_pizza a[fep];

    int i;

    for (i = 0; i < fep; i++)
    {
        a[i].id = i;
        a[i].deb = i * calcul_par_thread;
        a[i].fin = (i + 1) * calcul_par_thread;
        a[i].pop = pop;
        a[i].clts = clts;
        a[i].m = &m;
        a[i].sem = &sem;
        pthread_create(&thread[i], NULL, fep_note_pizza, (void *)&a[i]);
    }

    for (i = 0; i < fep; i++)
    {
        pthread_join(thread[i], NULL);
    }

    for (i = fep * calcul_par_thread; i < pop->nb_pzs; i++)
    {
        pop->notes[i] = pizza_note_pizza(pop->pzs[i], clts);
        if (pop->notes[m] < pop->notes[i])
            m = i;
    }

    pop->max_fit_index = m;
    return m;
}

int population_note_pizzas(population *pop, clients *clts, int fep)
{
    pop->notes_sum = -1;
    if (fep > 1)
    {
        return population_note_pizzas_fep(pop, clts, fep);
    }
    else
    {
        return population_note_pizzas_classic(pop, clts);
    }
}

int roulette(population *pop)
{
    int *notes = pop->notes;
    int len = pop->nb_pzs;
    int max_fit_index = pop->max_fit_index;
    int s = pop->notes_sum;
    int i, r, prob, note;
    double coeff = 30.0 / notes[max_fit_index];
    // Obtenir un nombre aléatoire
    r = rand();
    // Calculer la somme des notes
    if (s == -1)
    {
        s = 0;
        for (i = 0; i < len; i++)
        {
            note = (int)(notes[i] * coeff);

            prob = note * note;
            if (i == max_fit_index)
            {
                prob = prob * note;
            }

            s = s + prob;
        }
        pop->notes_sum = s;
    }
    if (s == 0)
        return r % len;
    // On prend r dans [0, s[
    r = r % s;
    // Boucle pour trouver l'indice
    for (i = 0; (r >= 0 && i < len); i++)
    {
        note = (int)(notes[i] * coeff);

        prob = note * note;
        if (i == max_fit_index)
        {
            prob = prob * note;
        }
        r = r - prob;
    }
    return i - 1;
}

void population_nextgen_classic(population *pop, int max_fit_index)
{
    pizza **pzs_srce = pop->pzs;
    pizza **pzs_dest = pop->pzs_backup;

    for (int i = 0; i < pop->pzs[0]->nb_ingr; i++)
    {
        pzs_dest[0]->ingr[i] = pzs_srce[max_fit_index]->ingr[i];
    }

    for (int i = 1; i < pop->nb_pzs; i++)
    {
        pizza_enfant(
            pzs_dest[i],
            pzs_srce[roulette(pop)],
            pzs_srce[roulette(pop)],
            pzs_srce[roulette(pop)],
            pop->proba_mutation);
    }

    pop->pzs = pzs_dest;
    pop->pzs_backup = pzs_srce;
}

struct FEP_nextgen
{
    int id;
    pizza **pzs_srce;
    pizza **pzs_dest;
    int deb;
    int fin;
    population *pop;
};

void *fep_nextgen(void *arg)
{
    struct FEP_nextgen *a = (struct FEP_nextgen *)arg;
    int i_local;

    for (i_local = a->deb; i_local < a->fin; i_local++)
    {
        pizza_enfant(
            a->pzs_dest[i_local],
            a->pzs_srce[roulette(a->pop)],
            a->pzs_srce[roulette(a->pop)],
            a->pzs_srce[roulette(a->pop)],
            a->pop->proba_mutation);
    }

    pthread_exit(NULL);
}

void population_nextgen_fep(population *pop, int max_fit_index, int fep)
{
    pizza **pzs_srce = pop->pzs;
    pizza **pzs_dest = pop->pzs_backup;

    int calcul_par_thread = pop->nb_pzs / fep;

    pthread_t thread[fep];
    struct FEP_nextgen a[fep];

    int i;

    for (i = 0; i < pop->pzs[0]->nb_ingr; i++)
    {
        pzs_dest[0]->ingr[i] = pzs_srce[max_fit_index]->ingr[i];
    }

    for (i = 0; i < fep; i++)
    {
        a[i].id = i;
        if (i == 0)
            a[i].deb = 1;
        else
            a[i].deb = i * calcul_par_thread;
        a[i].fin = (i + 1) * calcul_par_thread;
        a[i].pzs_srce = pzs_srce;
        a[i].pzs_dest = pzs_dest;
        a[i].pop = pop;
        pthread_create(&thread[i], NULL, fep_nextgen, (void *)&a[i]);
    }

    for (i = 0; i < fep; i++)
    {
        pthread_join(thread[i], NULL);
    }

    for (i = fep * calcul_par_thread; i < pop->nb_pzs; i++)
    {
        pizza_enfant(
            a->pzs_dest[i],
            a->pzs_srce[roulette(a->pop)],
            a->pzs_srce[roulette(a->pop)],
            a->pzs_srce[roulette(a->pop)],
            a->pop->proba_mutation);
    }

    pop->pzs = pzs_dest;
    pop->pzs_backup = pzs_srce;
}

void population_nextgen(population *pop, int max_fit_index, int fep)
{
    if (fep > 1)
    {
        population_nextgen_fep(pop, max_fit_index, fep);
    }
    else
    {
        population_nextgen_classic(pop, max_fit_index);
    }
}
