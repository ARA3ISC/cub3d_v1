/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:35:47 by maneddam          #+#    #+#             */
/*   Updated: 2023/08/19 21:03:12 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// int encode_rgb(int r, int g, int b) {
//     return ((r << 16) | (g << 8) | b);
// }

void	my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color)
{
	char	*dst;

	if(y > 700)
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

// 	deltaX = fabs(m->inf->p.m.x - m->inf->p.stepMoveX);
// 	deltaY = fabs(m->inf->p.m.y - m->inf->p.stepMoveY);


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

int		getXpmPixel(t_mlx_data *data, int x, int y)
{
	char	*dst;

	dst = data->inf->txts[0].addr + (y * data->inf->txts[0].line_length + x * (data->inf->txts[0].bits_per_pixel / 8));
	// printf(RED"*********************\n"RESET);
	return *(unsigned int*)dst;
}


int get_column(t_mlx_data *m)
{
	if (m->inf->p.m.vertical)
	{
		// printf("horizontaljjj\n");
		return ((double)(((int)(m->inf->p.m.y)) % 60)/60) * m->inf->txts[0].width;
	}
	else if (m->inf->p.m.horizontal)
	{
		// printf("verticaljjjj\n");
		return ((double)(((int)(m->inf->p.m.x )) % 60)/60) * m->inf->txts[0].width;
	}
	return ((double)(((int)(m->inf->p.m.x )) % 60)/60) * m->inf->txts[0].width;

	// if((int)(m->inf->p.m.y + 0.5) % 60 == 0)
	// if((int)(m->inf->p.m.x + 0.5) % 60 == 0)
		
	// int x = (((int)(m->inf->p.m.x + 0.5)) % 60);
	// int y = (((int)(m->inf->p.m.y + 0.5)) % 60);

	// if(x >= y)
	// 	return ((double)(x)/60) * m->inf->txts[0].width;
	// else 
	// 	return ((double)(y)/60) * m->inf->txts[0].width;
	// return 0;
}

void draw_wall(t_mlx_data *m, double wall_heigth, int s)
{
	double inc =  0;
	double d =  700 / 2 - wall_heigth /2;
		// double x = s * (m->inf->txts[0].width / wall_heigth);

	
	// int x = (m->inf->p.m.x/60 - (int)(m->inf->p.m.x / 60))* m->inf->txts[0].width;
	double c = m->inf->txts[0].height / wall_heigth ;
	double y = 0;
	// double r = m->inf->txts[0].width / wall_heigth;
	
	while (inc < wall_heigth)
	{
		my_mlx_pixel_put(m, s, d++, getXpmPixel(m, get_column(m), y));
		// printf("s : %d  ---- c : %f\n", s,c);
		y += c ;
		// y++;
		// if (y > m->inf->txts[0].height)
		// 	break;
		inc++;
	}
	// printf("c %d %f\n",  m->inf->txts[0].height, wall_heigth);
	
}



void draw_rays(t_mlx_data *m, double beta, int s)
{
	int i = 0;
	int k;
	get_second_point(m, 0, beta);
	// printf("angle : %f\n", beta * 180/M_PI ) ;
	while(!hasWallat_for_line(m, m->inf->p.m.x  , m->inf->p.m.y ))
	{

		get_second_point(m, i, beta);
		if(hasWallat_for_line(m, m->inf->p.m.x + m->inf->p.x_direction , m->inf->p.m.y  + m->inf->p.y_direction))
			break;
		
		k = 0;
		while(k < m->inf->y_len * 60)
		{
			s = 0;
			if (k == (int)(m->inf->p.m.y))
			{
				while(s < m->inf->max_len * 60)
				{
					if (s == (int)(m->inf->p.m.x))
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
	// printf("y_direction : %d\n",m->inf->p.y_direction);
	if(m->inf->p.x_direction == 1)
		m->inf->p.m.x++;
	if(m->inf->p.y_direction == 1)
		m->inf->p.m.y++;
	// if(m->inf->p.x_direction == 1)
	// 	m->inf->p.stepMoveX++;
	// if(m->inf->p.y_direction == 1)
	// 	m->inf->p.stepMoveY++;
	// printf("mx : %f\nmy : %f\n", m->inf->p.m.x , m->inf->p.m.y );
	m->inf->p.m.horizontal = false;
	m->inf->p.m.vertical = false;
	// if((int)floor(m->inf->p.m.x) % 60 == 0 && (int)floor(m->inf->p.m.y) % 60 != 0)
	// 	m->inf->p.m.vertical = true;
	//  if((int)floor(m->inf->p.m.y) % 60 == 0 && (int)floor(m->inf->p.m.x) % 60 != 0)
	// 	m->inf->p.m.horizontal = true;
	if((int)floor(m->inf->p.m.x) % 60 == 0 && (int)floor(m->inf->p.m.y) % 60 != 0)
		m->inf->p.m.vertical = true;
	else if((int)floor(m->inf->p.m.y) % 60 == 0 && (int)floor(m->inf->p.m.x) % 60 != 0)
		m->inf->p.m.horizontal = true;
	else 
	{
		if((int)floor(m->inf->p.m.x + 1) % 60 == 0 && (int)floor(m->inf->p.m.y) % 60 != 0)
			m->inf->p.m.vertical = true;
		else
			m->inf->p.m.horizontal = true;

	}
		// printf("TAWA7DA\n");

}





void drawLine(t_mlx_data *m, double beta, int s)
{
	int i = 0;

	// bool horizontal = false;
	// bool vertical = false;
	// int k;
	(void)s;
	double ray_distance;
	double wall_heigth;

	// (void)wall_heigth;
	// double dis_to_v_wall;
	// while(i < 30)
	// printf("beta : %f\n", beta);
	get_second_point(m, 0, beta);

	while(!hasWallat_for_line(m, m->inf->p.m.x  , m->inf->p.m.y ))
	{

		get_second_point(m, i, beta);
		if(hasWallat_for_line(m, m->inf->p.m.x + m->inf->p.x_direction , m->inf->p.m.y  + m->inf->p.y_direction))
			break;
		i++;
	}
	// printf("y_direction : %d\n",m->inf->p.y_direction);
	if(m->inf->p.x_direction == 1)
		m->inf->p.m.x++;
	if(m->inf->p.y_direction == 1)
		m->inf->p.m.y++;
	// if(m->inf->p.x_direction == 1)
	// 	m->inf->p.stepMoveX++;
	// if(m->inf->p.y_direction == 1)
	// 	m->inf->p.stepMoveY++;
	m->inf->p.m.x = floor(m->inf->p.m.x);
	m->inf->p.m.y = floor(m->inf->p.m.y);
	m->inf->p.m.horizontal = false;
	m->inf->p.m.vertical = false;
	// if((int)floor(m->inf->p.m.x) % 60 == 0 && (int)floor(m->inf->p.m.y) % 60 != 0)
	// 	m->inf->p.m.vertical = true;
	//  if((int)floor(m->inf->p.m.y) % 60 == 0 && (int)floor(m->inf->p.m.x) % 60 != 0)
	// 	m->inf->p.m.horizontal = true;
	if((int)(m->inf->p.m.x) % 60 == 0 && (int)(m->inf->p.m.y) % 60 != 0)
		m->inf->p.m.vertical = true;
	else if((int)(m->inf->p.m.y) % 60 == 0 && (int)(m->inf->p.m.x) % 60 != 0)
		m->inf->p.m.horizontal = true;
	else 
	{
		if((int)(m->inf->p.m.x + 1) % 60 == 0 && (int)(m->inf->p.m.y) % 60 != 0)
			m->inf->p.m.vertical = true;
		else
			m->inf->p.m.horizontal = true;

	}
	ray_distance = sqrt(pow(m->inf->p.m.x - m->inf->p.stepMoveX, 2) + pow(m->inf->p.m.y - m->inf->p.stepMoveY, 2)) * cos(beta - m->inf->p.rotationAngle);
	// printf("ray distance: %f\n", ray_distance);
	wall_heigth = (1300 * 60)/(2 * (tan(M_PI/6) * ray_distance));
	
	// printf("wall hiegth: %f\n", wall_heigth);
	printf("px : %f\npy : %f\n", m->inf->p.stepMoveX, m->inf->p.stepMoveY);

	
	draw_wall(m, wall_heigth, s);
}


void	drawPlayer(t_mlx_data *m)
{
	int	k;
	int	s;
	// int	color;
	// int middleX;m->inf->p.m.x
	// int middleY;
	// color = encode_rgb(0, 255, 128);
	// middleX = m->inf->max_len * 60/2;
	// middleY = m->inf->y_len * 60/2;
	// printf("stepx %f\nstepy : %f\n", m->inf->p.stepMoveX, m->inf->p.stepMoveY);

	k = 0;
	while (k < m->inf->y_len * 60)
	{
		s = 0;
		if (k == m->inf->p.stepMoveY)
		{
			while (s < m->inf->max_len * 60)
			{
				if ( s == m->inf->p.stepMoveX)
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
	double beta;
	// int temp = (M_PI / 3) / (m->inf->max_len * 60);
	// if(m->inf->p.rotationAngle > 0 && m->inf->p.rotationAngle < M_PI / 6)
	// 	beta = 2 * M_PI - (M_PI / 6 - m->inf->p.rotationAngle);
	// else 
	beta = m->inf->p.rotationAngle - (30 * M_PI) / 180; 
	if(beta <= 0 && beta >= -1 * (30 * M_PI) / 180)
		beta = 2 * M_PI + beta;              
	// double beta = m->inf->p.rotationAngle;
	while(s < m->inf->max_len * 20)
	{
		draw_rays(m, beta, s);
		// if (beta >= m->inf->p.rotationAngle + (30 * M_PI) / 180)
		// 	break;
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
	|| y < 0 || y > m->inf->y_len * 60) {
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
	m->img_ptr = mlx_new_image(m->mlx_ptr, 1300, 700);
	m->addr = mlx_get_data_addr(m->img_ptr, &m->bits_per_pixel, &m->line_length, &m->endian);
	

	while(i < 700)
	{
		j = 0;
		while(j < 1300)
		{
			if(i > 350)
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
	while(s < 1300)
	{
		drawLine(m, beta,s);
		// printf("jkkkkjjj\n");
		// if (beta >= m->inf->p.rotationAngle + M_PI / 6)
		// 	break;
		beta += M_PI / (3 * 1300 );
		s++;
	}
	
	mlx_put_image_to_window(m->mlx_ptr, m->wind_ptr, m->img_ptr, 0, 0);

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
		// printf("Xplayer : %f ||  px : %f\n Yolayer : %f ||  py : %f\n", m->inf->p.stepMoveX/60,(m->inf->p.stepMoveX + m->inf->p.x_direction * SPEED)/60, m->inf->p.stepMoveY/60,(m->inf->p.stepMoveY - m->inf->p.y_direction * SPEED)/60);
		// printf("posPlayerX : %f\nposPlayerY : %f\n", m->inf->p.stepMoveX, m->inf->p.stepMoveY);
		// printf("posX to check : %f\nposY to check : %f\n", m->inf->p.stepMoveX + (cos(m->inf->p.rotationAngle) * (SPEED)), m->inf->p.stepMoveY - (sin(m->inf->p.rotationAngle) * (SPEED)));
		if (hasWallat(m, m->inf->p.stepMoveX + (cos(m->inf->p.rotationAngle) * (SPEED)), m->inf->p.stepMoveY -  (sin(m->inf->p.rotationAngle) * (SPEED))))
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
		if (hasWallat(m, m->inf->p.stepMoveX - (cos(m->inf->p.rotationAngle) * (SPEED)) + m->inf->p.x_direction, m->inf->p.stepMoveY + (sin(m->inf->p.rotationAngle) * (SPEED)) + m->inf->p.y_direction))
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
		// printf("hahaha\n");
		m->inf->p.rotationAngle -= M_PI / 80;
	}

	// printf("NewAngle : %f\n2*PI : %f\n", m->inf->p.rotationAngle, 2 * M_PI);
	if (m->inf->p.rotationAngle > 2 * M_PI)
		m->inf->p.rotationAngle = M_PI /80;
	if (m->inf->p.rotationAngle < 0)
		m->inf->p.rotationAngle = 2 * M_PI - M_PI/80;
	render3d(m);
	displayMap(m, m->inf);
	// m->inf->p.x_direction = 0;
	// m->inf->p.y_direction = 0;

	// drawPlayer(m, m->inf->p.y , m->inf->p.x );
	return 0;
}

void draw_ori_ray(t_mlx_data *mlx, int i, int j)
{
	int s;
	int k;

	// printf("i : %d\nj : %d\n", i, j);
	// printf("map2d[i] : %c\n", mlx->inf->map2d[i][]);

	// 	return true;
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

// void draw_rays(t_mlx_data *mlx)
// {
// 	int i;
// 	int j;
// 	int k;
// 	int s;

// 	i = (int)mlx->inf->p.y_tmp;
// 	j = (int)mlx->inf->p.x_tmp;
// 	double d = get_decimal_number(mlx->inf->p.x_tmp);
// 	double r = get_decimal_number(mlx->inf->p.y_tmp);
// 	// printf("x :: %f\ny :: %f\n", mlx->inf->p.x_tmp, mlx->inf->p.y_tmp);
// 		k = 0;
// 		while (k < 60)
// 		{
// 			s = 0;
// 			if(k >= 60 * d)
// 			{
// 				while (s < 60)
// 				{
// 					if (s == 60 * r)
// 					{
// 						my_mlx_pixel_put(mlx, k + (j * 60), s + (i * 60), 0xFF0000);
// 					}
// 					s++;
// 				}
// 			}
// 			k++;
// 		}
// }

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

	mlx.wind_ptr = mlx_new_window(mlx.mlx_ptr, 1300,  700, "cub3d");
	mlx.img_ptr = mlx_new_image(mlx.mlx_ptr, 1300,  700);
	mlx.addr = mlx_get_data_addr(mlx.img_ptr, &mlx.bits_per_pixel, &mlx.line_length, &mlx.endian);


	// mlx.inf->txts = malloc(4 * sizeof(t_texts));
	getTextures(&mlx);

	mlx.inf->p.stepMoveX = mlx.inf->p.x * 60 + 30;
	mlx.inf->p.stepMoveY = mlx.inf->p.y * 60 + 30;

	initailize_directions(&mlx);
	mlx.inf = inf;
	render3d(&mlx);
	displayMap(&mlx, inf);
	mlx_hook(mlx.wind_ptr, 2, 1L<<0, move, &mlx);
	// mlx_hook(mlx.wind_ptr, 2, 1L<<1, keyRelease, &mlx);
	mlx_loop(mlx.mlx_ptr);

}
