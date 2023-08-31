/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 00:57:15 by eej-jama          #+#    #+#             */
/*   Updated: 2023/08/31 23:34:17 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	first_h_inters(t_mlx_data *m, double alpha)
{
	if (sin(alpha * RAD) > 0)
	{
		m->inf->m_h.y = (int)(m->inf->p.y_position / SQUARE_SIZE) * SQUARE_SIZE - 0.0001;
		m->inf->m_h.x = m->inf->p.x_position + (m->inf->p.y_position - m->inf->m_h.y) / tan(alpha * RAD);
	}
	else if (sin(alpha * RAD) < 0)
	{
		m->inf->m_h.y = (int)((m->inf->p.y_position + SQUARE_SIZE) / SQUARE_SIZE) * SQUARE_SIZE;
		m->inf->m_h.x = m->inf->p.x_position + (m->inf->p.y_position - m->inf->m_h.y) / tan(alpha * RAD);
	}
	 if (alpha == 180.00)
	{
		m->inf->m_h.y = m->inf->p.y_position;
		m->inf->m_h.x = 0;
	}
	if (alpha == 0.00 || alpha == 360.000000)
	{
		m->inf->m_h.y = m->inf->p.y_position;
		m->inf->m_h.x = m->inf->max_len * SQUARE_SIZE;
	}
	return (sqrt(pow(m->inf->m_h.x - m->inf->p.x_position, 2) + pow(m->inf->m_h.y - m->inf->p.y_position, 2)));
}

double	first_v_inters(t_mlx_data *m, double alpha)
{
	if (cos(alpha * RAD) > 0)
	{
		m->inf->m_v.x = floor((m->inf->p.x_position + SQUARE_SIZE) / SQUARE_SIZE) * SQUARE_SIZE;
		m->inf->m_v.y = m->inf->p.y_position - tan(alpha * RAD) * (m->inf->m_v.x - m->inf->p.x_position);
	}
	else if (cos(alpha * RAD) < 0)
	{
		// printf("%f\n", cos(alpha * RAD));
		m->inf->m_v.x = floor((m->inf->p.x_position) / SQUARE_SIZE) * SQUARE_SIZE - 0.0001;
		m->inf->m_v.y = m->inf->p.y_position - tan(alpha * RAD) * (m->inf->m_v.x - m->inf->p.x_position);
	}
	if (alpha == 90.00)
	{
		m->inf->m_v.x = m->inf->p.x_position;
		m->inf->m_v.y = 0;
	}
	if (alpha == 270.000000)
	{
		m->inf->m_v.y = m->inf->y_len * SQUARE_SIZE;
		m->inf->m_v.x = m->inf->p.x_position;
	}

	return (sqrt(pow(m->inf->m_v.x - m->inf->p.x_position, 2) + pow(m->inf->m_v.y - m->inf->p.y_position, 2)));
}

bool	is_wall_for_ray(t_mlx_data *m, double x, double y)
{
	if (x < 0 || y < 0 || x >= m->inf->max_len * SQUARE_SIZE || y >= m->inf->y_len * SQUARE_SIZE)
		return true;

	// printf(GREEN"\n----x----- %f | -----y----- %f\n",x, y);
	// if ( m->inf->map2d[gridY][gridX] == '1' || m->inf->map2d[(int)m->inf->p.m.y/60][gridX] == '1' || m->inf->map2d[gridY][(int)m->inf->p.m.x/60] == '1' )
	if (m->inf->map2d[(int)(floor(y / SQUARE_SIZE))][(int)(floor(x / SQUARE_SIZE))] == '1')
		return true;
	return false;
}
bool	is_wall(t_mlx_data *m, double x, double y)
{
	int grid_x;
	int grid_y;
	if (x < 0 || y < 0 || x >= m->inf->max_len * SQUARE_SIZE || y >= m->inf->y_len * SQUARE_SIZE)
		return true;

	grid_x = (int)(floor(x / SQUARE_SIZE));
	grid_y = (int)(floor(y / SQUARE_SIZE));
	// printf(GREEN"\n----x----- %f | -----y----- %f\n",x, y);
	// if ( m->inf->map2d[gridY][gridX] == '1' || m->inf->map2d[(int)m->inf->p.m.y/60][gridX] == '1' || m->inf->map2d[gridY][(int)m->inf->p.m.x/60] == '1' )
	if (m->inf->map2d[grid_y][grid_x] == '1' || m->inf->map2d[(int)(m->inf->p.y_position / SQUARE_SIZE)][grid_x] == '1'
	|| m->inf->map2d[grid_y][(int)(m->inf->p.x_position / SQUARE_SIZE)] == '1' || m->inf->map2d[grid_y][grid_x] == 32)
		return true;
	return false;
}
double get_h_dist_to_wall(t_mlx_data *m, double alpha)
{
	if (alpha == 0.00 || alpha == 180.00 || alpha == 360.00)
	{
		m->inf->m_h.y = m->inf->p.y_position;
		m->inf->m_h.x = m->inf->max_len * SQUARE_SIZE - 0.0001;
		return INT_MAX;
	}
	if (sin(alpha * RAD) > 0 && cos(alpha * RAD) > 0)
	{
		m->inf->m_h.y -= SQUARE_SIZE;
		m->inf->m_h.x += SQUARE_SIZE / tan(alpha * RAD);
	}
	else if (sin(alpha * RAD) > 0 && cos(alpha * RAD) < 0)
	{
		m->inf->m_h.y -= SQUARE_SIZE;
		m->inf->m_h.x -= -SQUARE_SIZE / tan(alpha * RAD);
	}
	else if (sin(alpha * RAD) < 0 && cos(alpha * RAD) > 0)
	{
		m->inf->m_h.y += SQUARE_SIZE;
		m->inf->m_h.x -= SQUARE_SIZE / tan(alpha * RAD);
	}
	else if (sin(alpha * RAD) < 0 && cos(alpha * RAD) < 0)
	{
		m->inf->m_h.y += SQUARE_SIZE;
		m->inf->m_h.x -= SQUARE_SIZE / tan(alpha * RAD);
	}
	return (sqrt(pow(m->inf->m_h.x - m->inf->p.x_position, 2) + pow(m->inf->m_h.y - m->inf->p.y_position, 2)));
}

double get_v_dist_to_wall(t_mlx_data *m, double alpha)
{
	if (alpha == 0.00 || alpha == 360.00)
	{
		m->inf->m_v.x += SQUARE_SIZE;
		m->inf->m_v.y = m->inf->p.y_position;
	}
	if (alpha == 270.00)
	{
		m->inf->m_v.x = m->inf->p.x_position;
		m->inf->m_v.y = m->inf->y_len * SQUARE_SIZE - SQUARE_SIZE * 2;
		return INT_MAX;
	}
	else if (cos(alpha * RAD) > 0 && sin(alpha * RAD) > 0)
	{
		m->inf->m_v.x += SQUARE_SIZE;
		m->inf->m_v.y -= tan(alpha * RAD) * SQUARE_SIZE;
	}
	else if (cos(alpha * RAD) > 0 && sin(alpha * RAD) < 0)
	{
		// printf("ggggggggggggggggggggggggg\n");
		m->inf->m_v.x += SQUARE_SIZE;
		m->inf->m_v.y -= tan(alpha * RAD) * SQUARE_SIZE;
	}
	else if (cos(alpha * RAD) < 0 && sin(alpha * RAD) > 0)
	{
		m->inf->m_v.x -= SQUARE_SIZE;
		m->inf->m_v.y += tan(alpha * RAD) * SQUARE_SIZE;
	}
	else if (cos(alpha * RAD) < 0 && sin(alpha * RAD) < 0)
	{
		m->inf->m_v.x -= SQUARE_SIZE;
		m->inf->m_v.y += tan(alpha * RAD) * SQUARE_SIZE;
	}

	return (sqrt(pow(m->inf->m_v.x - m->inf->p.x_position, 2) + pow(m->inf->m_v.y - m->inf->p.y_position, 2)));
}

void	draw_rays(t_mlx_data *m, double alpha)
{
	// double alpha;
	double h_distance;
	double v_distance;


	h_distance = first_h_inters(m, alpha);
	v_distance = first_v_inters(m, alpha);


	while (!is_wall_for_ray(m, m->inf->m_h.x, m->inf->m_h.y))
	{
		h_distance = get_h_dist_to_wall(m, alpha);
	}
	m->inf->m_h.y = round(m->inf->m_h.y);
	// printf("h_dist : %f\n", h_distance);
	while (!is_wall_for_ray(m, m->inf->m_v.x, m->inf->m_v.y))
	{
		v_distance = get_v_dist_to_wall(m, alpha);
	}
	m->inf->m_v.y = round(m->inf->m_v.y);
	// printf("v_dist : %f\n", v_distance);

	if (h_distance < v_distance)
		print_ray(m, m->inf->p.x_position, m->inf->p.y_position, m->inf->m_h.x,  m->inf->m_h.y, 0x00FF00);
	else
		print_ray(m, m->inf->p.x_position, m->inf->p.y_position, m->inf->m_v.x,  m->inf->m_v.y, 0x00FF00);
}
