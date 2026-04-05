/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlobun <rlobun@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 17:04:43 by rlobun            #+#    #+#             */
/*   Updated: 2026/04/05 17:04:44 by rlobun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPH_H
# define GRAPH_H
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>

struct	s_scene;

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

void	init_mlx(struct s_scene *scene);
void	start_mlx_loop(struct s_scene *scene);
void	destroy_mlx(t_graph *mlx);
int		mlx_signals(int keycode, void *param);
int		mlx_close(void *param);

#endif
