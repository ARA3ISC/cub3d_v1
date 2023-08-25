/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:41:47 by maneddam          #+#    #+#             */
/*   Updated: 2023/08/18 12:24:31 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line/get_next_line.h"
# include "mlx_Linux/mlx.h"
#include <stdint.h>
# include <math.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define PURPLE "\e[35m"
# define RESET "\n\033[0m"
# define GREEN "\033[0;32m"
# define RED "\033[0;31m"

# define SPACE 0x2BE3E8
# define WALL 0x1300C3F
# define PLAYER 0x2CA0F6


# define ESC 65307
# define W 119
# define D 100
# define A 97
# define S 115
# define RIGHT 65363
# define LEFT 65361
# define UP 126
# define DOWN 125
# define SPEED 3
# define WINDOW_HEIGHT 700
# define WINDOW_WIdTH 1300
# define PIXEL_CASE 60
# define MINIMAP_PERCENT 0.2

typedef struct s_point
{
	double x;
	double y;
	double x_minimap;
	double y_minimap;
	bool vertical;
	bool horizontal;
}	t_point;

typedef struct s_player
{
	double	x;
	double	y;
	double	x_startPos;
	double	y_startPos;
	double	x_tmp;
	double	y_tmp;
	double stepMoveX;
	double stepMoveY;
	double stepMoveX_minimap;
	double stepMoveY_minimap;

	char direction;

	int x_direction;
	int y_direction;
	double rotationAngle;
	t_point m;
}				t_player;

typedef struct s_mlx_data
{
	void		*mlx_ptr;
	void		*wind_ptr;
	void		*img_ptr;
	char		**map2d;

	struct s_infos *inf;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	*addr;

}				t_mlx_data;

typedef struct s_texts
{
	void		*mlx_ptr;
	void		*img_ptr;
	int			width;
	int			height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	*addr;
}			t_texts;

typedef struct s_infos
{
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;

	int			*F;
	int			*C;
	char		*infosArr[6];
	int			parameters;
	int			mapStartIndex;
	char		**map2d;
	char		*map1d;
	int			y_len;
	int			max_len;
	int			index_max_len;
	double 		percent_h_mini;
	double 		percent_w_mini;
	t_player	p;

	t_texts		txts[4];

	// int y_len;
}				t_infos;

void			draw_rays(t_mlx_data *m, double beta, int s);

void			printError(char *msg);
void			parsing(char *argv, t_infos *infos);
char			*get_next_line(int fd);
char			*ft_strjoin_free(char *s1, char *s2);
char			*ft_strjoin_char(char *s1, char c);
int				ft_strcmp(char *s1, char *s2);

void			getNord(char *readLine, t_infos *infos, int pos);
void			getSouth(char *readLine, t_infos *infos, int pos);
void			getWest(char *readLine, t_infos *infos, int pos);
void			getEast(char *readLine, t_infos *infos, int pos);
void			getFloor(char *readLine, t_infos *infos, int pos);
void			getCeiling(char *readLine, t_infos *infos, int pos);

bool			isCompound(t_infos *infos);
void			handleFloorDetails(char *readLine, t_infos *infos);
void			handleCeilingDetails(char *readLine, t_infos *infos);
void			countCommas(char *readLine);
void			invalidCharacters(char *readline);
int				countWords(char *str);
void			invalidForm(char *readLine);
void			handleMap(char *fullmap, t_infos *infos);

void			handlePlayer(char **map, t_infos *infos);
char			**reFormeMap(char **map2d, t_infos *infos);

void			reycasting(t_infos *inf);
t_player	player_pos(char **table_2d);
bool hasWallat(t_mlx_data *m, double x, double y);
bool hasWallat_for_line(t_mlx_data *m, double x, double y);
int rgb_to_hex(int red, int green, int blue);
#endif
