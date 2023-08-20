/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:35:47 by maneddam          #+#    #+#             */
/*   Updated: 2023/08/20 19:12:45 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// int encode_rgb(int r, int g, int b) {
//     return ((r << 16) | (g << 8) | b);
// }

void	my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	drawSpace(t_mlx_data *m, int x, int y)
{
	int	k;
	int	s;

	k = 0;
	while (k < 60)
	{
		s = 0;
		while (s < 60)
		{
			if (s == 0 || k == 0)
				my_mlx_pixel_put(m , s + (60 * x), k + (60 * y) * 0.001, 0x000000);
			else
				my_mlx_pixel_put(m , s + (60 * x), k + (60 * y), SPACE);
			s++;
		}
		k++;
	}

}
void circle(t_mlx_data *m, int x, int y, int radius, int color) {
  int i, j;

  for (i = -radius; i <= radius; i++) {
    for (j = -radius; j <= radius; j++) {
      if (i * i + j * j <= radius * radius) {
        my_mlx_pixel_put(m, x + i, y + j , color);
      }
    }
  }
}

void	drawSquare(t_mlx_data *m, int x, int y)
{
	int	k;
	int	s;

	k = 0;
	while (k < 60)
	{
		s = 0;
		while (s < 60)
		{
			if (s == 0 || k == 0)
				my_mlx_pixel_put(m , s + (60 * x), k + (60 * y), 0x000000);
			else
				my_mlx_pixel_put(m , s + (60 * x), k + (60 * y), WALL);
			s++;
		}
		k++;
	}

}

void	initailize_directions(t_mlx_data *m)
{
	if (m->inf->map2d[(int)m->inf->p.y][(int)m->inf->p.x] == 'N')
	{
		m->inf->p.rotationAngle = M_PI / 2;
		m->inf->p.y_direction = -1;
	}
	else if (m->inf->map2d[(int)m->inf->p.y][(int)m->inf->p.x] == 'S')
	{
		printf("dkhl\n");
		m->inf->p.rotationAngle = 3 * M_PI / 2;
		m->inf->p.y_direction = 1;
	}
	else if (m->inf->map2d[(int)m->inf->p.y][(int)m->inf->p.x] == 'E')
	{
		m->inf->p.rotationAngle = 0;
		m->inf->p.x_direction = 1;
	}
	else if (m->inf->map2d[(int)m->inf->p.y][(int)m->inf->p.x] == 'W')
	{
		m->inf->p.rotationAngle = M_PI;
		m->inf->p.x_direction = -1;
	}
}

void get_second_point(t_mlx_data *m, int i, double beta)
{
	if (m->inf->p.rotationAngle < (M_PI / 2) && m->inf->p.rotationAngle > ((M_PI * 3) / 2))
		m->inf->p.x_direction = 1;
	if (m->inf->p.rotationAngle < (3 * M_PI / 2) && m->inf->p.rotationAngle > (M_PI / 2))
		m->inf->p.x_direction = -1;

	if (m->inf->p.rotationAngle < (M_PI * 2) && m->inf->p.rotationAngle > (M_PI))
		m->inf->p.y_direction = 1;
	if (m->inf->p.rotationAngle < M_PI && m->inf->p.rotationAngle > 0)
		m->inf->p.y_direction = -1;


	m->inf->p.m->x = m->inf->p.stepMoveX + (cos(beta) * i);

	// printf("->%d\nstepMovget_second_pointY : %f\nangle : %f\n", m->inf->p.y_direction , m->inf->p.stepMoveY, beta);
	// printf("stepMovY : %f\nstepMoveX : %f\n",m->inf->p.stepMoveY, m->inf->p.stepMoveX);
	m->inf->p.m->y = m->inf->p.stepMoveY - (sin(beta) * i);
}

// void	draw_trace(t_mlx_data *m)
// {
// 	int k;
// 	int s;
// 	double deltaX;
// 	double deltaY;
// 	double stepX;
// 	double stepY;
// 	double deltaMax;


// 	k = m->inf->p.stepMoveY;
// 	s = m->inf->p.stepMoveX;

// 	deltaX = fabs(m->inf->p.m->x - m->inf->p.stepMoveX);
// 	deltaY = fabs(m->inf->p.m->y - m->inf->p.stepMoveY);


// 	// if (deltaX > deltaY)
// 	// {
// 	// 	stepX = deltaX / deltaX;
// 	// 	stepY = deltaY / deltaX;
// 	// }
// 	deltaMax = fmax(deltaX, deltaY);

// 	stepX = 60 * deltaX / deltaMax;
// 	stepY = 60 * deltaY / deltaMax;
// 	int i = 0;

// 	// deltaY = m->inf->p.stepMoveY;
// 	while(i <= m->inf->p.stepMoveY)
// 	{
// 		printf("s : %d\nk : %d\n", s, k);
// 		printf("stepX : %f\nstepY : %f\n", stepX, stepY);
// 		my_mlx_pixel_put(m, s , k, 0xFFFFFF);
// 		s += stepX;
// 		k += stepY;
// 		i++;
// 	}


// }



void draw_trace(t_mlx_data *m)
{
	int s;
	int k;

	int i;

	s = m->inf->p.stepMoveY + 1;
	k = m->inf->p.stepMoveX + 1;

	i = m->inf->p.stepMoveY + 1;

	while(i < m->inf->p.stepMoveY + 30 )
	{
		my_mlx_pixel_put(m, k , s, 0xFFFFFF);
		printf("s : %d\nk = %d\n", s, k);
		s++;
		k++;
		i++;
	}
}

void drawLine(t_mlx_data *m, double beta)
{
	int s;
	int k;
	int i = 0;
	// while(i < 30)
		get_second_point(m, 0, m->inf->p.rotationAngle);
	while(!hasWallat(m, m->inf->p.m->x +2 * m->inf->p.x_direction, m->inf->p.m->y + 2* m->inf->p.y_direction))
	{
		get_second_point(m, i, beta);
		k = 0;
		while(k < m->inf->y_len * 60 )
		{

			s = 0;
			if (k == (int)(m->inf->p.m->y))
			{
				while(s < m->inf->max_len * 60)
				{
					if (s == (int)(m->inf->p.m->x))
					{
						my_mlx_pixel_put(m, s , k, 0xf9ff79);
					}

					s++;
				}
			}
			k++;
		}
		i++;
	}
	// printf("mx : %f\nmy : %f\n",m->inf->p.m->x, m->inf->p.m->y);
	// printf("angle : %f\n", m->inf->p.rotationAngle);
	// draw_trace(m);

}


void	drawPlayer(t_mlx_data *m, int x, int y)
{
	int	k;
	int	s;
	(void)x;
	(void)y;
	// int	color;
	// int middleX;
	// int middleY;
	// color = encode_rgb(0, 255, 128);
	// middleX = m->inf->max_len * 60/2;
	// middleY = m->inf->y_len * 60/2;
	// printf("stepx %f\nstepy : %f\n", m->inf->p.stepMoveX, m->inf->p.stepMoveY);
	k = 0;
	while (k < m->inf->y_len * 60)
	{
		s = 0;
		if (k == (int)m->inf->p.stepMoveY - 1 || k == (int)m->inf->p.stepMoveY || k == (int)m->inf->p.stepMoveY + 1)
		{
			while (s < m->inf->max_len * 60)
			{
				if (s == (int)m->inf->p.stepMoveX - 1 || s == (int)m->inf->p.stepMoveX  || s == (int)m->inf->p.stepMoveX + 1)
				{
					my_mlx_pixel_put(m, s , k, 0xFFFFFF);

					// circle(m, m->inf->p.stepMoveX , m->inf->p.stepMoveY, 3, 0xFFFFFF);
				}
				s++;
			}
		}
		k++;
	}



	s = 0;
	// int temp = (M_PI / 3) / (m->inf->max_len * 60);

	double beta = m->inf->p.rotationAngle - (30 * M_PI) / 180;

	while(s < m->inf->max_len * 20)
	{
		drawLine(m, beta);
		if (beta >= m->inf->p.rotationAngle + (30 * M_PI) / 180)
			break;
		beta += M_PI / (3 * m->inf->max_len * 20);
		s++;
	}
	// drawRay

}

void	displayMap(t_mlx_data *m, t_infos *inf)
{

	char	**map2d;
	int		i;
	int		j;

	i = 0;
	map2d = inf->map2d;
	mlx_destroy_image(m->mlx_ptr, m->img_ptr);
	m->img_ptr = mlx_new_image(m->mlx_ptr, inf->max_len * 60, inf->y_len * 60);
	m->addr = mlx_get_data_addr(m->img_ptr, &m->bits_per_pixel, &m->line_length, &m->endian);
	m->inf = inf;

	while (map2d[i])
	{
		j = 0;
		while (map2d[i][j])
		{
			if (map2d[i][j] == '1' || map2d[i][j] == 32)
				drawSquare(m, j, i);
			else
				drawSpace(m, j, i);
			// if (map2d[i][j] == '0')
			// 	drawSquare(m, i, j, 'S');
			j++;
		}
		i++;
	}
	drawPlayer(m, inf->p.x * 60, inf->p.y * 60);
	// draw_rays(m);
	mlx_put_image_to_window(m->mlx_ptr, m->wind_ptr, m->img_ptr, 0, 0);
}

bool hasWallat(t_mlx_data *m, double x, double y)
{
	int gridX;
	int gridY;
	if (x < 0 || x > m->inf->max_len * 60
	|| y < 0 || y > m->inf->y_len * 60) {
			return true;
	}
	// printf("y-> %f\n", y);
	// printf("x-> %f\n", x);

	gridX = (int)(x / 60);
	gridY = (int)(y / 60);
	return m->inf->map2d[gridY][gridX] == '1';
}

int	keyRelease(int keycode, t_mlx_data *m)
{
	(void)keycode;
	m->inf->p.x_direction = 0;
	m->inf->p.y_direction = 0;
	return 0;
}

int	move(int keycode, t_mlx_data *m)
{
	// printf("uuuuu %d\n", keycode);
	if (keycode == ESC)
	{
		printf("You closed the game using ESC key !");
		mlx_destroy_window(m->mlx_ptr, m->wind_ptr);
		exit(0);
	}
	if (keycode == W)
	{
		printf("px : %f\npy : %f\n", m->inf->p.stepMoveX, m->inf->p.stepMoveY);
		if (hasWallat(m, m->inf->p.stepMoveX + (cos(m->inf->p.rotationAngle) * (SPEED)), m->inf->p.stepMoveY - (sin(m->inf->p.rotationAngle) * (SPEED))))
		{
			printf("WALL\n");
			return 0;
		}
		// m->inf->p.stepMoveY -=  SPEED ;
		m->inf->p.stepMoveY -= (sin(m->inf->p.rotationAngle) * (SPEED));
		m->inf->p.stepMoveX += (cos(m->inf->p.rotationAngle) * (SPEED));
		// printf("angle : %f\n", m->inf->p.rotationAngle);
		// printf("must return 0 : %f\n", (sin(m->inf->p.rotationAngle) * (SPEED)));
		// printf("must not return 314: %f\n",  m->inf->p.stepMoveY);
	}
	if (keycode == S)
	{
		if (hasWallat(m, m->inf->p.stepMoveX - (cos(m->inf->p.rotationAngle) * (SPEED)), m->inf->p.stepMoveY + (sin(m->inf->p.rotationAngle) * (SPEED))))
		{
			printf("WALL\n");
			return 0;
		}
		m->inf->p.stepMoveY += (sin(m->inf->p.rotationAngle) * (SPEED));
		m->inf->p.stepMoveX -= (cos(m->inf->p.rotationAngle) * (SPEED));
		// m->inf->p.stepMoveY += sin(m->inf->p.rotationAngle) * SPEED ;
		// m->inf->p.stepMoveX -= cos(m->inf->p.rotationAngle) * SPEED;
	}
	if (keycode == D)
	{
		if (hasWallat(m, m->inf->p.stepMoveX - (cos(m->inf->p.rotationAngle + (M_PI/2)) * (SPEED)), m->inf->p.stepMoveY + (sin(m->inf->p.rotationAngle + (M_PI/2)) * (SPEED))))
		{
			printf("WALL\n");
			return 0;
		}
		// m->inf->p.stepMoveX += SPEED;
		m->inf->p.stepMoveY += (sin(m->inf->p.rotationAngle + (M_PI/2)) * (SPEED)) ;
		m->inf->p.stepMoveX -= (cos(m->inf->p.rotationAngle + (M_PI/2)) * (SPEED));
		// m->inf->p.stepMoveX -= cos(m->inf->p.rotationAngle) * SPEED;
	}
	if (keycode == A)
	{
		if (hasWallat(m, m->inf->p.stepMoveX + (cos(m->inf->p.rotationAngle - (M_PI * 3/2)) * (SPEED)), m->inf->p.stepMoveY - (sin(m->inf->p.rotationAngle - (M_PI * 3/2)) * (SPEED))))
		{
			printf("WALL\n");
			return 0;
		}
		m->inf->p.stepMoveY -= (sin(m->inf->p.rotationAngle - (M_PI * 3/2)) * (SPEED)) ;
		m->inf->p.stepMoveX += (cos(m->inf->p.rotationAngle - (M_PI * 3/2)) * (SPEED));
	}
	if (keycode == LEFT)
	{
		m->inf->p.rotationAngle += M_PI / 80;
	}
	if (keycode == RIGHT)
	{
		printf("hahaha\n");
		m->inf->p.rotationAngle -= M_PI / 80;
	}

	// printf("NewAngle : %f\n2*PI : %f\n", m->inf->p.rotationAngle, 2 * M_PI);
	if (m->inf->p.rotationAngle > 2 * M_PI)
		m->inf->p.rotationAngle = 0;
	displayMap(m, m->inf);
	m->inf->p.x_direction = 0;
	m->inf->p.y_direction = 0;

	// drawPlayer(m, m->inf->p.y , m->inf->p.x );
	return 0;
}

void draw_ori_ray(t_mlx_data *mlx, int i, int j)
{
	int s;
	int k;

	// printf("i : %d\nj : %d\n", i, j);
	// printf("map2d[i] : %c\n", mlx->inf->map2d[i][]);

	while(mlx->inf->map2d[i])
	{
		k = 0;
		// if(i )
		while (k < 60)
		{
			s = 0;
			while (s < 60)
			{
				if (s == 30)
				{
					my_mlx_pixel_put(mlx, k + (j), s + (i), 0x000);
				}
				s++;
			}
			k++;
		}



		// my_mlx_pixel_put(mlx, 30 + (i), 30 + (j), 0xFFFFFF);
		i++;
	}
}

double get_decimal_number(double a)
{
	double b;

	b = (int)a;
	return (a - b);
}

void draw_rays(t_mlx_data *mlx)
{
	int i;
	int j;
	int k;
	int s;

	i = (int)mlx->inf->p.y_tmp;
	j = (int)mlx->inf->p.x_tmp;
	double d = get_decimal_number(mlx->inf->p.x_tmp);
	double r = get_decimal_number(mlx->inf->p.y_tmp);
	printf("x :: %f\ny :: %f\n", mlx->inf->p.x_tmp, mlx->inf->p.y_tmp);
		k = 0;
		while (k < 60)
		{
			s = 0;
			if(k >= 60 * d)
			{
				while (s < 60)
				{
					if (s == 60 * r)
					{
						my_mlx_pixel_put(mlx, k + (j * 60), s + (i * 60), 0xFF0000);
					}
					s++;
				}
			}
			k++;
		}
}

void	reycasting(t_infos *inf)
{
	t_mlx_data	mlx;

	inf->p = player_pos(inf->map2d);
	inf->p.x_direction = 0;
	inf->p.y_direction = 0;
	// ! N E W S
	inf->p.rotationAngle = 0;
	mlx.inf = inf;
	mlx.map2d = inf->map2d;

	mlx.mlx_ptr = mlx_init();

	// printf("x) %f\ny) %f\n", inf->p.x, inf->p.y);

	mlx.wind_ptr = mlx_new_window(mlx.mlx_ptr, inf->max_len * 60, inf->y_len * 60, "cub3d");
	mlx.img_ptr = mlx_new_image(mlx.mlx_ptr, inf->max_len * 60, inf->y_len * 60);
	mlx.addr = mlx_get_data_addr(mlx.img_ptr, &mlx.bits_per_pixel, &mlx.line_length, &mlx.endian);

	mlx.inf->p.x_tmp = mlx.inf->p.x + 0.5;
	mlx.inf->p.y_tmp = mlx.inf->p.y + 0.5;
	mlx.inf->p.stepMoveX = mlx.inf->p.x * 60;
	mlx.inf->p.stepMoveY = mlx.inf->p.y * 60;

	initailize_directions(&mlx);
	displayMap(&mlx, inf);

	mlx_hook(mlx.wind_ptr, 2, 1L<<0, move, &mlx);
	// mlx_hook(mlx.wind_ptr, 2, 1L<<1, keyRelease, &mlx);
	mlx_loop(mlx.mlx_ptr);

}
