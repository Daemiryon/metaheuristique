#ifndef _GRAPH_
#define _GRAPH_

#include <time.h>
#include <stdio.h>
#include <unistd.h>

extern const char *graph;

void graph_open();
void graph_close();
void graph_write_gen(int iterate, int score);
void graph_write_recuit(double T, int score);

#endif /* _GRAPH_ */