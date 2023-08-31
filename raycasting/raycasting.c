/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 23:30:29 by eej-jama          #+#    #+#             */
/*   Updated: 2023/08/31 23:16:34 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_player(t_mlx_data *m)
{
	int	k;
	int	s;
	// int	i;

	k = 0;
	while (k < 60 * m->inf->y_len)
	{
		s = 0;
		if (k == floor(m->inf->p.y_position))
		{
			while (s < 60 * m->inf->max_len)
			{
				if (s == floor(m->inf->p.x_position))
					circle(m, m->inf->p.x_position,
						m->inf->p.y_position, 2, 0xFF0000);
				s++;
			}
		}
		k++;
	}


	// print_ray(m, m->inf->p.x_position, m->inf->p.y_position,
	// 	m->inf->p.x_position,  m->inf->p.y_position - 30, 0xFF0000);



	// draw_rays(m, m->inf->p.rotationAngle);
}

void	draw_space(t_mlx_data *m, int x, int y)
{
	int	k;
	int	s;

	k = 0;
	while (k < 60)
	{
		s = 0;
		while (s < 60)
		{
			if (s == 0 || k == 0)
				my_mlx_pixel_put(m , s + (60 * x), k + (60 * y) * 0.001, 0x000000);
			else
				my_mlx_pixel_put(m, s + (x * SQUARE_SIZE  ),
				k + (y * SQUARE_SIZE ), SPACE);
			s++;
		}
		k++;
	}
}

void	draw_square(t_mlx_data *m, int x, int y)
{
	int	k;
	int	s;

	k = 0;

	while (k < 60)
	{
		s = 0;
		while (s < 60)
		{

			if (s == 0 || k == 0)
				my_mlx_pixel_put(m , s + (60 * x), k + (60 * y) * 0.001, 0x000000);
			else
				my_mlx_pixel_put(m, s + (x * SQUARE_SIZE ),
				k + (y * SQUARE_SIZE ), 0x5B235C);
			s++;
		}
		k++;
	}
}

void	display_map(t_mlx_data *m, t_infos *inf)
{
	int		i;
	int		j;

	mlx_destroy_image(m->mlx_ptr, m->img_ptr);
	m->img_ptr = mlx_new_image(m->mlx_ptr, m->inf->max_len * 60, m->inf->max_len * 60);
	m->addr = mlx_get_data_addr(m->img_ptr, &m->bits_per_pixel, &m->line_length, &m->endian);
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
	double alpha = m->inf->p.rotationAngle - 30;
	// int s = 0;
	// // if(alpha < 0 && alpha > -30)
	// // 	alpha = 360 + alpha;
	// while(s >= 0)
	// {
		draw_rays(m, alpha);
	// 	alpha += 0.1;
	// 	if(alpha > m->inf->p.rotationAngle + 30)
	// 		break;
	// 	s++;
	// }

	mlx_put_image_to_window(m->mlx_ptr, m->wind_ptr, m->img_ptr, 0, 0);
}

void	raycasting(t_infos *inf)
{
	(void)inf;
	t_mlx_data	mlx;

	// inf->p.x_position = inf->p.x_start_pos;
	// inf->p.y_position = inf->p.y_start_pos;


	inf->p = player_pos(inf->map2d);
	mlx.map2d = inf->map2d;
	mlx.inf = inf;
	mlx.mlx_ptr = mlx_init();
	mlx.wind_ptr = mlx_new_window(mlx.mlx_ptr, WINDOW_WIdTH,  WINDOW_HEIGHT, "cub3d");
	mlx.img_ptr = mlx_new_image(mlx.mlx_ptr, WINDOW_WIdTH,  WINDOW_HEIGHT);
	mlx.addr = mlx_get_data_addr(mlx.img_ptr, &mlx.bits_per_pixel, &mlx.line_length, &mlx.endian);
	// // getTextures(&mlx);
	initailize_angle(&mlx);
	mlx.inf->p.x_position = mlx.inf->p.x_start_pos * SQUARE_SIZE + SQUARE_SIZE/2;
	mlx.inf->p.y_position = mlx.inf->p.y_start_pos * SQUARE_SIZE + SQUARE_SIZE/2;

	// printf("xpos : %f\nypos : %f\n", mlx.inf->p.x_position / 60, mlx.inf->p.y_position / 60);
	// display_map(&mlx, inf);
	render3d(&mlx);

	mlx_hook(mlx.wind_ptr, 2, 1L<<0, move, &mlx);
	// // mlx_mouse_hook(mlx.wind_ptr, mouse_hook, &mlx);
	mlx_loop(mlx.mlx_ptr);
}
