/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_mvmnt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 00:20:23 by eej-jama          #+#    #+#             */
/*   Updated: 2023/08/31 23:16:40 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	move(int keycode, t_mlx_data *m)
{
	if (keycode == ESC)
	{
		printf("You closed the game using ESC key !");
		mlx_destroy_window(m->mlx_ptr, m->wind_ptr);
		exit(0);
	}
	if (keycode == W)
	{
		if(is_wall(m, m->inf->p.x_position + (cos(m->inf->p.rotationAngle * RAD) * (SPEED * 1.5)),
				m->inf->p.y_position - (sin(m->inf->p.rotationAngle * RAD) * (SPEED * 1.5))))
			return 0;
		m->inf->p.y_position -= (sin(m->inf->p.rotationAngle * RAD) * (SPEED));
		m->inf->p.x_position += (cos(m->inf->p.rotationAngle * RAD) * (SPEED));
	}
	if (keycode == S)
	{
		if(is_wall(m, m->inf->p.x_position - (cos(m->inf->p.rotationAngle * RAD) * (SPEED * 1.5)),
				m->inf->p.y_position + (sin(m->inf->p.rotationAngle * RAD) * (SPEED * 1.5))))
			return 0;
		m->inf->p.y_position += (sin(m->inf->p.rotationAngle * RAD) * (SPEED));
		m->inf->p.x_position -= (cos(m->inf->p.rotationAngle * RAD) * (SPEED));
	}
	if (keycode == D)
	{
		if(is_wall(m, m->inf->p.x_position - (cos((m->inf->p.rotationAngle + 90) * RAD ) * (SPEED * 1.5)),
				m->inf->p.y_position + (sin((m->inf->p.rotationAngle + 90) * RAD ) * (SPEED * 1.5)) ))
			return 0;
		m->inf->p.y_position += (sin((m->inf->p.rotationAngle + 90) * RAD ) * (SPEED)) ;
		m->inf->p.x_position -= (cos((m->inf->p.rotationAngle + 90) * RAD ) * (SPEED));
	}
	if (keycode == A)
	{
		if(is_wall(m, m->inf->p.x_position + (cos((m->inf->p.rotationAngle - 270) * RAD) * (SPEED * 1.5)),
				m->inf->p.y_position - (sin((m->inf->p.rotationAngle - 270)  * RAD) * (SPEED * 1.5))  ))
			return 0;
		m->inf->p.y_position -= (sin((m->inf->p.rotationAngle - 270)  * RAD) * (SPEED)) ;
		m->inf->p.x_position += (cos((m->inf->p.rotationAngle - 270) * RAD) * (SPEED));
	}
	if (keycode == LEFT)
	{
		m->inf->p.rotationAngle += 2;
	}
	if (keycode == RIGHT)
		m->inf->p.rotationAngle -= 2;


	if (m->inf->p.rotationAngle > 360)
		m->inf->p.rotationAngle = 2;
	if (m->inf->p.rotationAngle < 0)
		m->inf->p.rotationAngle = 358;

	// printf("rotation  : %f\n", m->inf->p.rotationAngle);
	render3d(m);
	// display_map(m, m->inf);

	return 0;
}
