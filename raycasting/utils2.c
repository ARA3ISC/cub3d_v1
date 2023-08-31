/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 00:14:58 by eej-jama          #+#    #+#             */
/*   Updated: 2023/08/31 03:42:27 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void draw_pixel(t_mlx_data *data, int x, int y, int color)
{
    if (x > data->inf->max_len * 60 || x < 0 || y > data->inf->y_len * 60
        || y < 0)
        return ;
    my_mlx_pixel_put(data, x, y, color);
}

void print_ray(t_mlx_data *data, int x0, int y0, int x1, int y1, int color)
{
	// if( x1 < 0)
	// 	return ;
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        draw_pixel(data, x0, y0, color); // Assuming white color (RGB format)
        if (x0 == x1 && y0 == y1)
            break;
        int err2 = 2 * err;
        if (err2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (err2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}
