/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_tool_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 09:36:48 by eej-jama          #+#    #+#             */
/*   Updated: 2023/08/26 15:49:56 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"




void	my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color)
{
	char	*dst;

	if(y > WINDOW_HEIGHT)
		return ;
	if(y < 0)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		getXpmPixel(t_mlx_data *data, int x, int y, int i)
{
	char	*dst;

	if(y > data->inf->txts[i].height)
		return 0;
	dst = data->inf->txts[i].addr + (y * data->inf->txts[i].line_length + x * (data->inf->txts[i].bits_per_pixel / 8));
	// printf(RED"*********************\n"RESET);
	return *(unsigned int*)dst;
}
