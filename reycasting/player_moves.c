/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 09:47:26 by eej-jama          #+#    #+#             */
/*   Updated: 2023/08/26 16:08:24 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool hasWallat(t_mlx_data *m, double x, double y)
{
	int gridX;
	int gridY;

	if (x < 0 || x > m->inf->max_len * 60
	|| y < 0 || y > m->inf->y_len * 60) {
			return true;
	}
	gridX = floor((x  / 60));
	gridY = floor((y  / 60));
	if ( m->inf->map2d[gridY][gridX] == 32 || m->inf->map2d[gridY][gridX] == '1' || m->inf->map2d[(int)m->inf->p.stepMoveY/60][gridX] == '1' || m->inf->map2d[gridY][(int)m->inf->p.stepMoveX/60] == '1' )
		return true;
	return false;
}

int mouse_hook(int keycode, int x, int y, t_mlx_data *mlx)
{
	(void)mlx;
	(void)x;
	(void)y;
	if(keycode == 4)
	{
		mlx->inf->p.rotationAngle += M_PI/80;
	}
	if(keycode == 5)
		mlx->inf->p.rotationAngle -= M_PI/80;

	if (mlx->inf->p.rotationAngle > 2 * M_PI)
		mlx->inf->p.rotationAngle = M_PI /80;
	if (mlx->inf->p.rotationAngle < 0)
		mlx->inf->p.rotationAngle = 2 * M_PI - M_PI/80;
	render3d(mlx);
	displayMap(mlx, mlx->inf);
	return 0;
}


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
		if (hasWallat(m, m->inf->p.stepMoveX + (cos(m->inf->p.rotationAngle) * (SPEED)), m->inf->p.stepMoveY + 2 * SPEED * m->inf->p.y_direction))
			return 0;
		m->inf->p.stepMoveY -= (sin(m->inf->p.rotationAngle) * (SPEED));
		m->inf->p.stepMoveX += (cos(m->inf->p.rotationAngle) * (SPEED));
		m->inf->p.stepMoveY_minimap -= (sin(m->inf->p.rotationAngle) * (SPEED * m->inf->percent_h_mini));
		m->inf->p.stepMoveX_minimap += (cos(m->inf->p.rotationAngle) * (SPEED * m->inf->percent_w_mini));
	}
	if (keycode == S)
	{
		if (hasWallat(m, m->inf->p.stepMoveX - (cos(m->inf->p.rotationAngle) * (SPEED)) , m->inf->p.stepMoveY + (sin(m->inf->p.rotationAngle) * (SPEED))))
			return 0;
		m->inf->p.stepMoveY += (sin(m->inf->p.rotationAngle) * (SPEED));
		m->inf->p.stepMoveX -= (cos(m->inf->p.rotationAngle) * (SPEED));
		m->inf->p.stepMoveY_minimap += (sin(m->inf->p.rotationAngle) * (SPEED * m->inf->percent_h_mini));
		m->inf->p.stepMoveX_minimap -= (cos(m->inf->p.rotationAngle) * (SPEED * m->inf->percent_w_mini));
	}
	if (keycode == D)
	{
		if (hasWallat(m, m->inf->p.stepMoveX - (cos(m->inf->p.rotationAngle + (M_PI/2)) * (SPEED)), m->inf->p.stepMoveY + (sin(m->inf->p.rotationAngle + (M_PI/2)) * (SPEED))))
			return 0;
		m->inf->p.stepMoveY += (sin(m->inf->p.rotationAngle + (M_PI/2)) * (SPEED)) ;
		m->inf->p.stepMoveX -= (cos(m->inf->p.rotationAngle + (M_PI/2)) * (SPEED));
		m->inf->p.stepMoveY_minimap += (sin(m->inf->p.rotationAngle + (M_PI/2)) * (SPEED * m->inf->percent_h_mini));
		m->inf->p.stepMoveX_minimap -= (cos(m->inf->p.rotationAngle + (M_PI/2)) * (SPEED * m->inf->percent_w_mini));
	}
	if (keycode == A)
	{
		if (hasWallat(m, m->inf->p.stepMoveX + 2 * m->inf->p.x_direction * (SPEED), m->inf->p.stepMoveY + 2 * m->inf->p.y_direction * (SPEED)))
			return 0;
		m->inf->p.stepMoveY -= (sin(m->inf->p.rotationAngle - (M_PI * 3/2)) * (SPEED)) ;
		m->inf->p.stepMoveX += (cos(m->inf->p.rotationAngle - (M_PI * 3/2)) * (SPEED));
		m->inf->p.stepMoveY_minimap -= (sin(m->inf->p.rotationAngle - (M_PI * 3/2)) * (SPEED * m->inf->percent_h_mini));
		m->inf->p.stepMoveX_minimap += (cos(m->inf->p.rotationAngle - (M_PI * 3/2)) * (SPEED * m->inf->percent_w_mini));
	}
	if (keycode == LEFT)
		m->inf->p.rotationAngle += M_PI / 80;
	if (keycode == RIGHT)
		m->inf->p.rotationAngle -= M_PI / 80;
	if (m->inf->p.rotationAngle > 2 * M_PI)
		m->inf->p.rotationAngle = M_PI /80;
	if (m->inf->p.rotationAngle < 0)
		m->inf->p.rotationAngle = 2 * M_PI - M_PI/80;
	render3d(m);
	displayMap(m, m->inf);
	return 0;
}
