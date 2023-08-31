/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 23:41:13 by eej-jama          #+#    #+#             */
/*   Updated: 2023/08/31 22:41:29 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	initailize_angle(t_mlx_data *m)
{
	if (m->inf->map2d[m->inf->p.y_start_pos][m->inf->p.x_start_pos] == 'N')
	{
		m->inf->p.rotationAngle = 90.00;
	}
	else if (m->inf->map2d[m->inf->p.y_start_pos][m->inf->p.x_start_pos] == 'S')
	{
		m->inf->p.rotationAngle = 270.00;
	}
	else if (m->inf->map2d[m->inf->p.y_start_pos][m->inf->p.x_start_pos] == 'E')
	{
		m->inf->p.rotationAngle = 0.00;
	}
	else if (m->inf->map2d[m->inf->p.y_start_pos][m->inf->p.x_start_pos] == 'W')
	{
		m->inf->p.rotationAngle = 180.00;
	}
}

void circle(t_mlx_data *m, int x, int y, int radius, int color)
{
  int i, j;

  for (i = -radius; i <= radius; i++) {
    for (j = -radius; j <= radius; j++) {
      if (i * i + j * j <= radius * radius) {
        my_mlx_pixel_put(m, x + i, y + j , color);
      }
    }
  }
}

void	my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color)
{
	char	*dst;

	if(x > WINDOW_WIdTH || y > WINDOW_HEIGHT || x < 0 || y < 0)
		return ;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
