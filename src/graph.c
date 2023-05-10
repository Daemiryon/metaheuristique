#include "graph.h"

const char *graph;
FILE* fd;
char buf[48];

void graph_open()
{
    if (graph != NULL)
        fd = fopen(graph, "w");
}

void graph_close()
{
    if (graph != NULL)
        fclose(fd);
}

void graph_write_gen(int iterate, int score)
{
    if (graph != NULL)
    {
        int k = sprintf(buf, "%d; %d\n",
            iterate,
            score);
        fwrite(buf, sizeof(char), k, fd);
    }
}

void graph_write_recuit(double T, int score)
{
    if (graph != NULL)
    {
        int k = sprintf(buf, "%f; %d\n",
            T,
            score);
        fwrite(buf, sizeof(char), k, fd);
    }
}
