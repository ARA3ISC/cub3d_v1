/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:35:47 by maneddam          #+#    #+#             */
/*   Updated: 2023/08/26 08:57:31 by eej-jama         ###   ########.fr       */
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

void	drawSpace(t_mlx_data *m, int x, int y)
{
	int	k;
	int	s;

	k = 0;
	while (k < WINDOW_HEIGHT * MINIMAP_PERCENT / m->inf->y_len  )
	{
		s = 0;
		while (s < WINDOW_WIdTH * MINIMAP_PERCENT / m->inf->max_len)
		{
			my_mlx_pixel_put(m ,    (s + (  x * PIXEL_CASE * m->inf->percent_w_mini )),    (k + (   y * PIXEL_CASE * m->inf->percent_h_mini )), SPACE);
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
	while (k < WINDOW_HEIGHT * MINIMAP_PERCENT / m->inf->y_len  )
	{
		s = 0;
		while (s < WINDOW_WIdTH * MINIMAP_PERCENT / m->inf->max_len)
		{
			my_mlx_pixel_put(m ,    (s + (  x * PIXEL_CASE * m->inf->percent_w_mini )),    (k + (   y * PIXEL_CASE * m->inf->percent_h_mini )), 0xFFFFFF);
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


void get_second_point_for_rays(t_mlx_data *m, int i, double beta)
{
	if (beta < (M_PI / 2) ||  beta > ((M_PI * 3) / 2))
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



int		getXpmPixel(t_mlx_data *data, int x, int y)
{
	char	*dst;

	if(y > data->inf->txts[0].height)
		return 0;
	dst = data->inf->txts[0].addr + (y * data->inf->txts[0].line_length + x * (data->inf->txts[0].bits_per_pixel / 8));
	// printf(RED"*********************\n"RESET);
	return *(unsigned int*)dst;
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

void draw_wall(t_mlx_data *m, double wall_heigth, int s)
{
	double inc =  0;
	double d =  WINDOW_HEIGHT / 2 - wall_heigth /2;
	double c = m->inf->txts[0].height / wall_heigth ;
	double y = 0;
	
	while (inc < wall_heigth)
	{
		my_mlx_pixel_put(m, s, d++, getXpmPixel(m, get_column(m), y));
		y += c;
		inc++;
	}
	
}


void draw_rays(t_mlx_data *m, double beta)
{
	int i;
	int k;
	int s;

	i = 0;
	while(i < 30 * MINIMAP_PERCENT)
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
					if ( s == floor(m->inf->p.m.x_minimap))
						my_mlx_pixel_put(m, s , k, 0xf9ff79);
					s++;
				}
			}
			k++;
		}
		i++;
	}
	if(m->inf->p.x_direction == 1)
		m->inf->p.m.x_minimap++;
	if(m->inf->p.y_direction == 1)
		m->inf->p.m.y_minimap++;
	m->inf->p.m.horizontal = false;
	m->inf->p.m.vertical = false;
	if((int)floor(m->inf->p.m.x_minimap) % PIXEL_CASE == 0 && (int)floor(m->inf->p.m.y_minimap) % PIXEL_CASE != 0)
		m->inf->p.m.vertical = true;
	else if((int)floor(m->inf->p.m.y_minimap) % PIXEL_CASE == 0 && (int)floor(m->inf->p.m.x_minimap) % PIXEL_CASE != 0)
		m->inf->p.m.horizontal = true;
	else 
	{
		if((int)floor(m->inf->p.m.x_minimap + 1) % PIXEL_CASE == 0 && (int)floor(m->inf->p.m.y_minimap) % PIXEL_CASE != 0)
			m->inf->p.m.vertical = true;
		else
			m->inf->p.m.horizontal = true;
	}
}





void drawLine(t_mlx_data *m, double beta, int s)
{
	int i = 0;

	double ray_distance;
	double wall_heigth;

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
		if((int)(m->inf->p.m.x + 1) % PIXEL_CASE == 0 && (int)(m->inf->p.m.y) % PIXEL_CASE != 0)
			m->inf->p.m.vertical = true;
		else
			m->inf->p.m.horizontal = true;

	}
	ray_distance = sqrt(pow(m->inf->p.m.x - m->inf->p.stepMoveX, 2) + pow(m->inf->p.m.y - m->inf->p.stepMoveY, 2)) * cos(beta - m->inf->p.rotationAngle);
	// printf("ray distance: %f\n", ray_distance);
	wall_heigth = (WINDOW_WIdTH * PIXEL_CASE)/(2 * (tan(M_PI/6) * ray_distance));
	
	// printf("wall hiegth: %f\n", wall_heigth);
	// printf("px : %f\npy : %f\n", m->inf->p.stepMoveX, m->inf->p.stepMoveY);

	
	draw_wall(m, wall_heigth, s);
}


void	drawPlayer(t_mlx_data *m)
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
				if ( s == floor(m->inf->p.stepMoveX_minimap))
				{
					circle(m, m->inf->p.stepMoveX_minimap , m->inf->p.stepMoveY_minimap, 2, 0xFF0000);
				}
				s++;
			}
		}
		k++;
	}
	draw_rays(m, m->inf->p.rotationAngle);
}

void	displayMap(t_mlx_data *m, t_infos *inf)
{

	int		i;
	int		j;
	

	
	i = 0;

	while (inf->map2d[i])
	{
		j = 0;
		while (inf->map2d[i][j])
		{
			if (inf->map2d[i][j] == '1' || inf->map2d[i][j] == 32)
				drawSquare(m, j, i);
			else
				drawSpace(m, j, i);
			j++;
		}
		i++;
	}

	drawPlayer(m);
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
	// if (x / 6 == 10)
	// 	return true;
	// printf("y-> %d\n", m->inf->y_len);
	// printf("x-> %d\n", m->inf->max_len);
	gridX = floor((x  / 60));
	gridY = floor((y  / 60));
	if ( m->inf->map2d[gridY][gridX] == 32 || m->inf->map2d[gridY][gridX] == '1' || m->inf->map2d[(int)m->inf->p.stepMoveY/60][gridX] == '1' || m->inf->map2d[gridY][(int)m->inf->p.stepMoveX/60] == '1' )
		return true;
	return false;
}


bool hasWallat_for_line(t_mlx_data *m, double x, double y)
{
	int gridX;
	int gridY;

	if (x < 0 || x > m->inf->max_len * 60 
	|| y < 0 || y > m->inf->y_len * 60 ) {
			return true;
	}

	// if((int)y % 60 == 0 && (int)x % 60 == 0)
	// {
	// 	printf("HELLO WORLD");
	// 	rethasWallat_for_lineurn true;
	// }

	
	// if (x / 6 == 10)
	// 	return true;
	// printf("y-> %d\n", m->inf->y_len);
	// printf("x-> %d\n", m->inf->max_len);

	gridX = floor((x  / 60));
	gridY = floor((y  / 60));
	if ( m->inf->map2d[gridY][gridX] == '1' || m->inf->map2d[(int)m->inf->p.m.y/60][gridX] == '1' || m->inf->map2d[gridY][(int)m->inf->p.m.x/60] == '1' )
		return true;
	return false;
}

int	keyRelease(int keycode, t_mlx_data *m)
{
	(void)keycode;
	m->inf->p.x_direction = 0;
	m->inf->p.y_direction = 0;
	return 0;
}

void render3d(t_mlx_data *m)
{
	int i = 0;
	int j = 0;
	int s;
	
	mlx_destroy_image(m->mlx_ptr, m->img_ptr);
	m->img_ptr = mlx_new_image(m->mlx_ptr, WINDOW_WIdTH, WINDOW_HEIGHT);
	m->addr = mlx_get_data_addr(m->img_ptr, &m->bits_per_pixel, &m->line_length, &m->endian);
	

	while(i < WINDOW_HEIGHT)
	{
		j = 0;
		while(j < WINDOW_WIdTH)
		{
			if(i > WINDOW_HEIGHT/2)
				my_mlx_pixel_put(m, j, i, rgb_to_hex(m->inf->F[0], m->inf->F[1], m->inf->F[2]));
			else
				my_mlx_pixel_put(m, j, i, rgb_to_hex(m->inf->C[0], m->inf->C[1], m->inf->C[2]));
				// my_mlx_pixel_put(m, j, i, WALL);

			j++;
		}
		i++;
	}
	
	

	s = 0;
	// int temp = (M_PI / 3) / (m->inf->max_len * 60);
	
	double beta = m->inf->p.rotationAngle - M_PI / 6;
	if(beta < 0 && beta > -(30 * M_PI) / 180)
		beta = 2 * M_PI + beta;
	// double beta = m->inf->p.rotationAngle;
	
	// printf("------------------------------------------------------------");
	while(s < WINDOW_WIdTH)
	{
		drawLine(m, beta,s);
		// printf("jkkkkjjj\n");
		// if (beta >= m->inf->p.rotationAngle + M_PI / 6)
		// 	break;
		beta += M_PI / (3 * WINDOW_WIdTH );
		s++;
	}
	
	mlx_put_image_to_window(m->mlx_ptr, m->wind_ptr, m->img_ptr, 0, 0);

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
	if (keycode == A)
	{
		if (hasWallat(m, m->inf->p.stepMoveX - (cos(m->inf->p.rotationAngle + (M_PI/2)) * (SPEED)), m->inf->p.stepMoveY + (sin(m->inf->p.rotationAngle + (M_PI/2)) * (SPEED))))
			return 0;
		m->inf->p.stepMoveY += (sin(m->inf->p.rotationAngle + (M_PI/2)) * (SPEED)) ;
		m->inf->p.stepMoveX -= (cos(m->inf->p.rotationAngle + (M_PI/2)) * (SPEED));
		m->inf->p.stepMoveY_minimap += (sin(m->inf->p.rotationAngle + (M_PI/2)) * (SPEED * m->inf->percent_h_mini));
		m->inf->p.stepMoveX_minimap -= (cos(m->inf->p.rotationAngle + (M_PI/2)) * (SPEED * m->inf->percent_w_mini));
	}
	if (keycode == D)
	{
		if (hasWallat(m, m->inf->p.stepMoveX + 2 * m->inf->p.x_direction * (SPEED), m->inf->p.stepMoveY + 2 * m->inf->p.y_direction * (SPEED)))
			return 0;
		m->inf->p.stepMoveY -= (sin(m->inf->p.rotationAngle - (M_PI * 3/2)) * (SPEED)) ;
		m->inf->p.stepMoveX += (cos(m->inf->p.rotationAngle - (M_PI * 3/2)) * (SPEED));
		m->inf->p.stepMoveY_minimap -= (sin(m->inf->p.rotationAngle - (M_PI * 3/2)) * (SPEED * m->inf->percent_h_mini));
		m->inf->p.stepMoveX_minimap += (cos(m->inf->p.rotationAngle - (M_PI * 3/2)) * (SPEED * m->inf->percent_w_mini));
	}
	if (keycode == LEFT)
		m->inf->p.rotationAngle -= M_PI / 80;
	if (keycode == RIGHT)
		m->inf->p.rotationAngle += M_PI / 80;
	if (m->inf->p.rotationAngle > 2 * M_PI)
		m->inf->p.rotationAngle = M_PI /80;
	if (m->inf->p.rotationAngle < 0)
		m->inf->p.rotationAngle = 2 * M_PI - M_PI/80;
	render3d(m);
	displayMap(m, m->inf);
	return 0;
}


double get_decimal_number(double a)
{
	double b;

	b = (int)a;
	return (a - b);
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

int handle_mouse(int x, int y, t_mlx_data *mlx)
{
	(void)y;
	 if (x < WINDOW_WIdTH / 2) {
        mlx->inf->p.rotationAngle -= M_PI/200;
    } else if (x > WINDOW_WIdTH / 2) {
        mlx->inf->p.rotationAngle += M_PI/200;
    }
	render3d(mlx);

	return 0;
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
	mlx.wind_ptr = mlx_new_window(mlx.mlx_ptr, WINDOW_WIdTH,  WINDOW_HEIGHT, "cub3d");
	mlx.img_ptr = mlx_new_image(mlx.mlx_ptr, WINDOW_WIdTH,  WINDOW_HEIGHT);
	mlx.addr = mlx_get_data_addr(mlx.img_ptr, &mlx.bits_per_pixel, &mlx.line_length, &mlx.endian);
	getTextures(&mlx);
	mlx.inf->percent_h_mini =  WINDOW_HEIGHT * MINIMAP_PERCENT / (mlx.inf->y_len * PIXEL_CASE);
	mlx.inf->percent_w_mini = WINDOW_WIdTH * MINIMAP_PERCENT /  (mlx.inf->max_len * PIXEL_CASE);
	mlx.inf->p.stepMoveX = mlx.inf->p.x * PIXEL_CASE + PIXEL_CASE/2;
	mlx.inf->p.stepMoveY = mlx.inf->p.y * PIXEL_CASE + PIXEL_CASE/2;
	mlx.inf->p.stepMoveX_minimap = (mlx.inf->p.x + 0.5) * PIXEL_CASE * mlx.inf->percent_w_mini;
	mlx.inf->p.stepMoveY_minimap = (mlx.inf->p.y + 0.5) * PIXEL_CASE * mlx.inf->percent_h_mini;
	initailize_directions(&mlx);
	mlx.inf = inf;
	render3d(&mlx);
	displayMap(&mlx, inf);
	mlx_hook(mlx.wind_ptr, 2, 1L<<0, move, &mlx);
	// mlx_hook(mlx.wind_ptr, 6, 1L<<6, &handle_mouse, &mlx);
	// mlx_hook(mlx.wind_ptr, 2, 1L<<1, keyRelease, &mlx);
	mlx_mouse_hook(mlx.wind_ptr, mouse_hook, &mlx);
	mlx_loop(mlx.mlx_ptr);

}
