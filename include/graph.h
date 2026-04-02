/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 12:00:00 by jaigonza          #+#    #+#             */
/*   Updated: 2026/04/02 12:00:00 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GRAPH_H
# define GRAPH_H
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>

struct s_scene;
typedef struct s_scene	t_scene;

typedef struct s_graph
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*address;
	int		bpp;
	int		line_length;
	int		endian;
}	t_graph;

void	init_mlx(t_scene *scene);
void	start_mlx_loop(t_scene *scene);
void	destroy_mlx(t_graph *mlx);
int		mlx_signals(int keycode, void *param);
int		mlx_close(void *param);

#endif
