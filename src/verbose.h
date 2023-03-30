#ifndef _VERBOSE_
#define _VERBOSE_

#include <time.h>
#include <stdio.h>
#include <unistd.h>

extern int verbose;

extern int verbose_initialized;
extern clock_t verbose_start_cpu_time;
extern time_t verbose_start_wall_time;
extern clock_t verbose_last_cpu_time;
extern time_t verbose_last_wall_time;

void verbose_time();
void verbose_section(const char* section_name);
void verbose_estimated(int nb_done, int nb_tot_todo);

#endif /* _VERBOSE_ */