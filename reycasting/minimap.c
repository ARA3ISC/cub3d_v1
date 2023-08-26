/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 09:34:01 by eej-jama          #+#    #+#             */
/*   Updated: 2023/08/26 10:39:08 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	get_second_point_for_rays(t_mlx_data *m, int i, double beta)
{
	if (beta < (M_PI / 2) || beta > ((M_PI * 3) / 2))
		m->inf->p.x_direction = 1;
	if (beta < (3 * M_PI / 2) && beta > (M_PI / 2))
		m->inf->p.x_direction = -1;
	if (beta < (M_PI * 2) && beta > (M_PI))
		m->inf->p.y_direction = 1;
	if (beta < M_PI && beta > 0)
		m->inf->p.y_direction = -1;
	m->inf->p.m.x_minimap = m->inf->p.stepMoveX_minimap + (cos(beta) * i);
	m->inf->p.m.y_minimap = m->inf->p.stepMoveY_minimap - (sin(beta) * i);
}

void	check_verticale_and_orizontal(t_mlx_data *m)
{
	if (m->inf->p.x_direction == 1)
		m->inf->p.m.x_minimap++;
	if (m->inf->p.y_direction == 1)
		m->inf->p.m.y_minimap++;
	m->inf->p.m.horizontal = false;
	m->inf->p.m.vertical = false;
	if ((int)floor(m->inf->p.m.x_minimap) % PIXEL_CASE == 0
		&& (int)floor(m->inf->p.m.y_minimap) % PIXEL_CASE != 0)
		m->inf->p.m.vertical = true;
	else if ((int)floor(m->inf->p.m.y_minimap) % PIXEL_CASE == 0
		&& (int)floor(m->inf->p.m.x_minimap) % PIXEL_CASE != 0)
		m->inf->p.m.horizontal = true;
	else 
	{
		if ((int)floor(m->inf->p.m.x_minimap + 1) % PIXEL_CASE == 0
			&& (int)floor(m->inf->p.m.y_minimap) % PIXEL_CASE != 0)
			m->inf->p.m.vertical = true;
		else
			m->inf->p.m.horizontal = true;
	}
}

void	draw_rays(t_mlx_data *m, double beta)
{
	int	i;
	int	k;
	int	s;

	i = 0;
	while (i < 30 * MINIMAP_PERCENT)
	{
		get_second_point_for_rays(m, i, beta);
		k = 0;
		while (k < WINDOW_HEIGHT * MINIMAP_PERCENT)
		{
			s = 0;
			if (k == floor(m->inf->p.m.y_minimap))
			{
				while (s < WINDOW_WIdTH * MINIMAP_PERCENT)
				{
					if (s == floor(m->inf->p.m.x_minimap))
						my_mlx_pixel_put(m, s, k, 0xf9ff79);
					s++;
				}
			}
			k++;
		}
		i++;
	}
	check_verticale_and_orizontal(m);
}

void	draw_space(t_mlx_data *m, int x, int y)
{
	int	k;
	int	s;

	k = 0;
	while (k < WINDOW_HEIGHT * MINIMAP_PERCENT / m->inf->y_len)
	{
		s = 0;
		while (s < WINDOW_WIdTH * MINIMAP_PERCENT / m->inf->max_len)
		{
			my_mlx_pixel_put(m, s + (x * PIXEL_CASE * m->inf->percent_w_mini),
				k + (y * PIXEL_CASE * m->inf->percent_h_mini), SPACE);
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
	while (k < WINDOW_HEIGHT * MINIMAP_PERCENT / m->inf->y_len)
	{
		s = 0;
		while (s < WINDOW_WIdTH * MINIMAP_PERCENT / m->inf->max_len)
		{
			my_mlx_pixel_put(m, s + (x * PIXEL_CASE * m->inf->percent_w_mini),
				k + (y * PIXEL_CASE * m->inf->percent_h_mini), 0xFFFFFF);
			s++;
		}
		k++;
	}
}

void	draw_player(t_mlx_data *m)
{
	int	k;
	int	s;

	k = 0;
	while (k < WINDOW_HEIGHT * MINIMAP_PERCENT)
	{
		s = 0;
		if (k == floor(m->inf->p.stepMoveY_minimap))
		{
			while (s < WINDOW_WIdTH * MINIMAP_PERCENT)
			{
				if (s == floor(m->inf->p.stepMoveX_minimap))
					circle(m, m->inf->p.stepMoveX_minimap,
						m->inf->p.stepMoveY_minimap, 2, 0xFF0000);
				s++;
			}
		}
		k++;
	}
	draw_rays(m, m->inf->p.rotationAngle);
}
