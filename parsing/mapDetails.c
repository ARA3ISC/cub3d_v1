/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapDetails.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 17:55:24 by maneddam          #+#    #+#             */
/*   Updated: 2023/08/11 16:49:54 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	handleFirstLine(char *firstline)
{
	int	i;

	i = 0;
	// printf("|%s|\n", firstline);
	while (firstline[i])
	{
		if (firstline[i] != 32 && firstline[i] != '\t' && firstline[i] != '1')
			printError("Invalid maaap");
		i++;
	}
}

void	handleLastLine(char *lastline)
{
	int	i;

	i = 0;
	while (lastline[i])
	{
		if (lastline[i] != 32 && lastline[i] != '\t' && lastline[i] != '1')
			printError("Invalid map");
		i++;
	}
}

int	get_y_len(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}
void	handleMiddleLines(char **map)
{
	int	i;
	int	j;

	i = 1;
	while (map[i])
	{
		j = 0;
		while (map[i][j] == 32 || map[i][j] == '\t')
			j++;
		if (map[i][j] && (map[i][j] != '1' || map[i][ft_strlen(map[i])
				- 1] == '0'))
			printError("Invalid maapi");
		i++;
	}
}
bool	isRestEmpty(char *rest)
{
	int	i;

	i = 1;
	while (rest[i])
	{
		if (rest[i] != 32 && rest[i] != '\t' && rest[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}

void	checkNestedNl(char *fullmap, t_infos *infos)
{
	int	i;

	i = 0;
	while (fullmap[i])
	{
		if (fullmap[i] == '1' && fullmap[i + 1] == '1' && fullmap[i + 2] == '1')
			break ;
		i++;
	}
	infos->map1d = fullmap + i;
	i = 0;
	if (infos->map1d[i] == '1' && infos->map1d[i + 1] == '1')
	{
		while (infos->map1d[i])
		{
			if (infos->map1d[i] == '1' && infos->map1d[i + 1] == '\n'
				&& infos->map1d[i + 2] == '\n' && !isRestEmpty(infos->map1d
					+ i))
				printError("Nested empty lines");
			i++;
		}
	}
}

void	handleWhiteSpaces(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '\t')
				printError("Invalid character");
			j++;
		}
		i++;
	}
}

void	handleMap(char *fullmap, t_infos *infos)
{
	char	**map2d;

	checkNestedNl(fullmap, infos);
	infos->y_len = 0;
	map2d = ft_split(fullmap, '\n');
	infos->map2d = ft_split(fullmap, '\n');
	// infos->map2d = &(map2d[infos->mapStartIndex]);
	infos->map2d = infos->map2d + infos->mapStartIndex;
	map2d = map2d + infos->mapStartIndex;
	handleWhiteSpaces(map2d);
	infos->y_len = get_y_len(infos->map2d);
	handleFirstLine(infos->map2d[0]);
	handleMiddleLines(infos->map2d);
	handleLastLine(infos->map2d[infos->y_len - 1]);
	handlePlayer(map2d, infos);
}
