#ifndef GRAPH_H
# define GRAPH_H
#include <mlx.h>
#include <stdio.h>
typedef struct s_graph
{
    void *mlx;
    void *mlx_win;
    void *img;
    char *address;
    int bpp;
    int line_len;
    int endian;
} t_graph;

void init_mlx(t_graph *mlx);

#endif
