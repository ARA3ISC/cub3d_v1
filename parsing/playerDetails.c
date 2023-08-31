/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playerDetails.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:26:43 by maneddam          #+#    #+#             */
/*   Updated: 2023/08/31 00:02:51 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_player	player_pos(char **table_2d)
{
	t_player	p;
	int			i;
	int			j;

	p.x = 0;
	p.y = 0;
	i = 0;
	while (table_2d[i])
	{
		j = 0;
		while (table_2d[i][j])
		{
			if (table_2d[i][j] == 'N' || table_2d[i][j] == 'E' || table_2d[i][j] == 'W'
				|| table_2d[i][j] == 'S')
			{
				p.x_start_pos = j;
				p.y_start_pos = i;
				return (p);
			}
			j++;
		}
		i++;
	}
	return (p);
}

void	playerPath(t_infos *infos, char **map, int x, int y)
{
	// printf("|%c|\n", map[y][x]);
	if (x < 0 || y < 0 || x > ft_strlen(map[y - 1]) || y > infos->y_len)
		return ;
	// printf("x) %d\ny) %d\n", x, y);
	if (map[y][x] == '1' || map[y][x] == '*')
		return ;
	// printf("***\n");
	if (map[y][x] == 32 || map[y][x] == '\t')
	{
		printError("Invalid path");
	}
	if (map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'S'
		|| map[y][x] == 'W' || map[y][x] == 'E')
	{
		map[y][x] = '*';
		playerPath(infos, map, x, y - 1);
		playerPath(infos, map, x + 1, y);
		playerPath(infos, map, x, y + 1);
		playerPath(infos, map, x - 1, y);
	}
}

void	handlePlayer(char **map2d, t_infos *infos)
{
	int	i;
	int	j;
	int	playerExist;

	i = 0;
	j = 0;
	playerExist = 0;
	while (infos->map2d[i])
	{
		j = 0;
		while (infos->map2d[i][j])
		{
			if (infos->map2d[i][j] == 'N' || infos->map2d[i][j] == 'S'
				|| infos->map2d[i][j] == 'W' || infos->map2d[i][j] == 'E')
			{
				playerExist++;
				infos->p.x_start_pos = j;
				infos->p.y_start_pos = i;
			}
			j++;
		}
		i++;
	}
	if (playerExist != 1)
		printError("It must be just one player");
	map2d = reFormeMap(map2d, infos);
	playerPath(infos, map2d, infos->p.x_start_pos, infos->p.y_start_pos);
}
