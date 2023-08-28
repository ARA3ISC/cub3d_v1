/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:35:47 by maneddam          #+#    #+#             */
/*   Updated: 2023/08/26 19:02:47 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"



void	initailize_directions(t_mlx_data *m)
{
	if (m->inf->map2d[(int)m->inf->p.y][(int)m->inf->p.x] == 'N')
	{
		m->inf->p.rotationAngle = M_PI / 2;
		m->inf->p.y_direction = -1;
	}
	else if (m->inf->map2d[(int)m->inf->p.y][(int)m->inf->p.x] == 'S')
	{
		printf("dkhl\n");
		m->inf->p.rotationAngle = 3 * M_PI / 2;
		m->inf->p.y_direction = 1;
	}
	else if (m->inf->map2d[(int)m->inf->p.y][(int)m->inf->p.x] == 'E')
	{
		m->inf->p.rotationAngle = 0;
		m->inf->p.x_direction = 1;
	}
	else if (m->inf->map2d[(int)m->inf->p.y][(int)m->inf->p.x] == 'W')
	{
		m->inf->p.rotationAngle = M_PI;
		m->inf->p.x_direction = -1;
	}
}

void	displayMap(t_mlx_data *m, t_infos *inf)
{

	int		i;
	int		j;



	i = 0;

	while (inf->map2d[i])
	{
		j = 0;
		while (inf->map2d[i][j])
		{
			if (inf->map2d[i][j] == '1' || inf->map2d[i][j] == 32)
				draw_square(m, j, i);
			else
				draw_space(m, j, i);
			j++;
		}
		i++;
	}

	draw_player(m);
	mlx_put_image_to_window(m->mlx_ptr, m->wind_ptr, m->img_ptr, 0, 0);
}

void render3d(t_mlx_data *m)
{
	int i;
	int j;
	int s;

	i = 0;
	j = 0;
	mlx_destroy_image(m->mlx_ptr, m->img_ptr);
	m->img_ptr = mlx_new_image(m->mlx_ptr, WINDOW_WIdTH, WINDOW_HEIGHT);
	m->addr = mlx_get_data_addr(m->img_ptr, &m->bits_per_pixel, &m->line_length, &m->endian);
	while(i < WINDOW_HEIGHT)
	{
		j = 0;
		while(j < WINDOW_WIdTH)
		{
			if(i > WINDOW_HEIGHT/2)
				my_mlx_pixel_put(m, j, i, rgb_to_hex(m->inf->F[0], m->inf->F[1], m->inf->F[2]));
			else
				my_mlx_pixel_put(m, j, i, rgb_to_hex(m->inf->C[0], m->inf->C[1], m->inf->C[2]));
			j++;
		}
		i++;
	}
	s = WINDOW_WIdTH;
	double beta = m->inf->p.rotationAngle - M_PI / 6;
	if(beta < 0 && beta > -(30 * M_PI) / 180)
		beta = 2 * M_PI + beta;
	while(s >= 0)
	{
		draw_line(m, beta,s);
		beta += M_PI / (3 * WINDOW_WIdTH );
		s--;
	}
	mlx_put_image_to_window(m->mlx_ptr, m->wind_ptr, m->img_ptr, 0, 0);
}


void	reycasting(t_infos *inf)
{
	t_mlx_data	mlx;

	inf->p = player_pos(inf->map2d);
	inf->p.x_direction = 0;
	inf->p.y_direction = 0;
	// ! N E W S
	inf->p.rotationAngle = 0;
	mlx.inf = inf;
	mlx.map2d = inf->map2d;
	mlx.mlx_ptr = mlx_init();
	mlx.wind_ptr = mlx_new_window(mlx.mlx_ptr, WINDOW_WIdTH,  WINDOW_HEIGHT, "cub3d");
	mlx.img_ptr = mlx_new_image(mlx.mlx_ptr, WINDOW_WIdTH,  WINDOW_HEIGHT);
	mlx.addr = mlx_get_data_addr(mlx.img_ptr, &mlx.bits_per_pixel, &mlx.line_length, &mlx.endian);
	getTextures(&mlx);
	mlx.inf->percent_h_mini =  WINDOW_HEIGHT * MINIMAP_PERCENT / (mlx.inf->y_len * PIXEL_CASE);
	mlx.inf->percent_w_mini = WINDOW_WIdTH * MINIMAP_PERCENT /  (mlx.inf->max_len * PIXEL_CASE);
	mlx.inf->p.stepMoveX = mlx.inf->p.x * PIXEL_CASE + PIXEL_CASE/2;
	mlx.inf->p.stepMoveY = mlx.inf->p.y * PIXEL_CASE + PIXEL_CASE/2;
	mlx.inf->p.stepMoveX_minimap = (mlx.inf->p.x + 0.5) * PIXEL_CASE * mlx.inf->percent_w_mini;
	mlx.inf->p.stepMoveY_minimap = (mlx.inf->p.y + 0.5) * PIXEL_CASE * mlx.inf->percent_h_mini;
	initailize_directions(&mlx);
	mlx.inf = inf;
	render3d(&mlx);
	displayMap(&mlx, inf);
	mlx_hook(mlx.wind_ptr, 2, 1L<<0, move, &mlx);
	mlx_mouse_hook(mlx.wind_ptr, mouse_hook, &mlx);
	mlx_loop(mlx.mlx_ptr);
}
