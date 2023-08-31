/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 22:14:21 by eej-jama          #+#    #+#             */
/*   Updated: 2023/08/31 23:41:43 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void draw_wall(t_mlx_data *m, double wall_heigth, int s, int i)
{
	double inc;
	(void)i;
	// printf("heigth : %f\n", wall_heigth);
	inc = 0;
	while (inc < wall_heigth / 2 )
	{
		my_mlx_pixel_put(m, s, 700 / 2 - inc, 0xE0D8D1);
		inc++;
	}
	inc  = 0;
	while (inc < wall_heigth / 2)
	{
		my_mlx_pixel_put(m, s, 700 / 2 + inc, 0xE0D8D1);
		inc++;
	}

}

int rgb_to_hex(int red, int green, int blue)
{
    return (red << 16) | (green << 8) | blue;
}

// void texture_selection(t_mlx_data *m, double wall_heigth, int s, double beta)
// {
// 	if( m->inf->p.m.horizontal)
// 	{
// 		if(sin(beta) > 0)
// 			draw_wall(m, wall_heigth, s, 1);
// 		else
// 			draw_wall(m, wall_heigth, s, 0);
// 	}
// 	else if (m->inf->p.m.vertical)
// 	{
// 		if(cos(beta) > 0)
// 			draw_wall(m, wall_heigth, s, 3);
// 		else
// 			draw_wall(m, wall_heigth, s, 2);
// 	}
// }

void draw_line(t_mlx_data *m, double alpha, int s)
{
	double h_distance;
	double v_distance;
	double wall_heigth;


	h_distance = first_h_inters(m, alpha);
	v_distance = first_v_inters(m, alpha);


	while (!is_wall_for_ray(m, m->inf->m_h.x, m->inf->m_h.y))
	{
		h_distance = get_h_dist_to_wall(m, alpha);
	}
	m->inf->m_h.y = round(m->inf->m_h.y) ;
	while (!is_wall_for_ray(m, m->inf->m_v.x, m->inf->m_v.y))
	{
		v_distance = get_v_dist_to_wall(m, alpha);
	}
	m->inf->m_v.y = round(m->inf->m_v.y) ;

	if (h_distance < v_distance)
	{
		wall_heigth = (WINDOW_WIdTH * SQUARE_SIZE)/(2 * (tan(30 * RAD) * (h_distance * cos((alpha - m->inf->p.rotationAngle) * RAD))));
		// printf("h_distanc : %f\n", h_distance);
	}
	else
	{
		wall_heigth = (WINDOW_WIdTH * SQUARE_SIZE)/(2 * (tan(30 * RAD) * (v_distance * cos((alpha - m->inf->p.rotationAngle) * RAD))));
		// printf("v_distanc : %f\n", v_distance);
	}
	printf("wall : %f\n", wall_heigth);
	draw_wall(m, wall_heigth, s, 2);
	// texture_selection(m,wall_heigth, s, alpha);
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
	s = 0;
	double alpha = m->inf->p.rotationAngle - 30;
	if(alpha < 0 && alpha > -30)
		alpha = 360 + alpha;
	// printf("angle : %f\n", m->inf->p.rotationAngle);
	while(s < WINDOW_WIdTH)
	{
		// if (alpha > 360)
		// 	alpha = 2;
		// if (alpha < 0)
		// 	alpha = 358;
		draw_line(m, alpha, s);
		printf("angle : %f\n", alpha);
		alpha += 60 / WINDOW_WIdTH;
		s++;
	}
	mlx_put_image_to_window(m->mlx_ptr, m->wind_ptr, m->img_ptr, 0, 0);
}
