/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 09:40:10 by eej-jama          #+#    #+#             */
/*   Updated: 2023/08/26 16:16:27 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


bool hasWallat_for_line(t_mlx_data *m, double x, double y)
{
	int gridX;
	int gridY;

	if (x < 0 || x > m->inf->max_len * 60
	|| y < 0 || y > m->inf->y_len * 60 ) {
			return true;
	}

	gridX = floor((x  / 60));
	gridY = floor((y  / 60));
	if ( m->inf->map2d[gridY][gridX] == '1' || m->inf->map2d[(int)m->inf->p.m.y/60][gridX] == '1' || m->inf->map2d[gridY][(int)m->inf->p.m.x/60] == '1' )
		return true;
	return false;
}




void draw_wall(t_mlx_data *m, double wall_heigth, int s, int i)
{
	double inc =  0;
	double d =  WINDOW_HEIGHT / 2 - wall_heigth /2;
	double c = m->inf->txts[i].height / wall_heigth ;
	double y = 0;

	while (inc < wall_heigth)
	{
		my_mlx_pixel_put(m, s, d++, getXpmPixel(m, get_column(m, i), y,  i));
		y += c;
		inc++;
	}

}

void get_second_point(t_mlx_data *m, int i, double beta)
{
	if (beta < (M_PI / 2) ||  beta > ((M_PI * 3) / 2))
		m->inf->p.x_direction = 1;
	if (beta < (3 * M_PI / 2) && beta > (M_PI / 2))
		m->inf->p.x_direction = -1;

	if (beta < (M_PI * 2) && beta > (M_PI))
		m->inf->p.y_direction = 1;
	if (beta < M_PI && beta > 0)
		m->inf->p.y_direction = -1;



	m->inf->p.m.x = m->inf->p.stepMoveX + (cos(beta) * i);
	m->inf->p.m.y = m->inf->p.stepMoveY - (sin(beta) * i);


}

void texture_selection(t_mlx_data *m, double wall_heigth, int s, double beta)
{
	if( m->inf->p.m.horizontal)
	{
		if(sin(beta) > 0)
			draw_wall(m, wall_heigth, s, 1);
		else
			draw_wall(m, wall_heigth, s, 0);
	}
	else if (m->inf->p.m.vertical)
	{
		if(cos(beta) > 0)
			draw_wall(m, wall_heigth, s, 3);
		else
			draw_wall(m, wall_heigth, s, 2);
	}
}

void draw_line(t_mlx_data *m, double beta, int s)
{
	int i;
	double ray_distance;
	double wall_heigth;

    i = 0;
	get_second_point(m, 0, beta);
	while(!hasWallat_for_line(m, m->inf->p.m.x  , m->inf->p.m.y ))
	{
		get_second_point(m, i, beta);
		if(hasWallat_for_line(m, m->inf->p.m.x + m->inf->p.x_direction , m->inf->p.m.y  + m->inf->p.y_direction))
			break;
		i++;
	}
	if(m->inf->p.x_direction == 1)
		m->inf->p.m.x++;
	if(m->inf->p.y_direction == 1)
		m->inf->p.m.y++;
	m->inf->p.m.x = floor(m->inf->p.m.x);
	m->inf->p.m.y = floor(m->inf->p.m.y);
	m->inf->p.m.horizontal = false;
	m->inf->p.m.vertical = false;
	if((int)(m->inf->p.m.x) % PIXEL_CASE == 0 && (int)(m->inf->p.m.y) % PIXEL_CASE != 0)
		m->inf->p.m.vertical = true;
	else if((int)(m->inf->p.m.y) % PIXEL_CASE == 0 && (int)(m->inf->p.m.x) % PIXEL_CASE != 0)
		m->inf->p.m.horizontal = true;
	else
	{
		if((sin(beta) > 0 && cos(beta) > 0) || (sin(beta) < 0 && cos(beta) < 0))
			m->inf->p.m.horizontal = true;
		else if ((sin(beta) < 0 && cos(beta)) > 0 || (sin(beta) < 0 && cos(beta) < 0))
			m->inf->p.m.vertical = true;
	}
	ray_distance = sqrt(pow(m->inf->p.m.x - m->inf->p.stepMoveX, 2) + pow(m->inf->p.m.y - m->inf->p.stepMoveY, 2)) * cos(beta - m->inf->p.rotationAngle);
	wall_heigth = (WINDOW_WIdTH * PIXEL_CASE)/(2 * (tan(M_PI/6) * ray_distance));
	texture_selection(m,wall_heigth,s,beta);
	// draw_wall(m, wall_heigth, s);
}
