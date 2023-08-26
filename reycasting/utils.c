/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 08:39:15 by eej-jama          #+#    #+#             */
/*   Updated: 2023/08/26 10:09:35 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3d.h"

int rgb_to_hex(int red, int green, int blue)
{
    return (red << 16) | (green << 8) | blue;
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

int get_column(t_mlx_data *m)
{
	if (m->inf->p.m.vertical)
	{
		return ((double)(((int)(m->inf->p.m.y)) % PIXEL_CASE)/PIXEL_CASE) * m->inf->txts[0].width;
	}
	else if (m->inf->p.m.horizontal)
	{
		return ((double)(((int)(m->inf->p.m.x )) % PIXEL_CASE)/PIXEL_CASE) * m->inf->txts[0].width;
	}
	return ((double)(((int)(m->inf->p.m.x )) % PIXEL_CASE)/PIXEL_CASE) * m->inf->txts[0].width;
}

void	getTextures(t_mlx_data *m)
{
	int i = 0;
	while (i < 4)
	{
		m->inf->txts[i].img_ptr = mlx_xpm_file_to_image(m->mlx_ptr, "./textures/wall1.xpm",
			&m->inf->txts[i].width, &m->inf->txts[i].height);
		
		if (!m->inf->txts[i].img_ptr)
			printError("xpm corrupted");
		
		m->inf->txts[i].addr = mlx_get_data_addr(m->inf->txts[i].img_ptr,
			&m->inf->txts[i].bits_per_pixel, &m->inf->txts[i].line_length, &m->inf->txts[i].endian);
		i++;
	}

}
