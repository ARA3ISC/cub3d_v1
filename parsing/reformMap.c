/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reformMap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:03:37 by maneddam          #+#    #+#             */
/*   Updated: 2023/08/12 13:24:57 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_strlen_tab(char *line)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (line)
	{
		while (line[i])
		{
			if (line[i] == '\t')
			{
				// printf("dkhel\n");
				len = len + 3;
			}
			i++;
			len++;
		}
	}
	return (len);
}

int	getBiggestLineIdex(char **map)
{
	int	i;
	int	biggest;
	int	index;

	i = 0;
	index = 0;
	biggest = ft_strlen(map[0]);
	while (map[i])
	{
		if (ft_strlen(map[i]) > biggest)
		{
			biggest = ft_strlen(map[i]);
			index = i;
		}
		i++;
	}
	return (index);
}

void	makeitRectangle(char **map, int maxlen)
{
	int	i;
	int	k;
	int	currentlen;

	i = 0;
	while (map[i])
	{
		currentlen = ft_strlen(map[i]);
		if (currentlen < maxlen)
		{
			k = 0;
			while (k < maxlen - currentlen)
			{
				map[i] = ft_strjoin_char(map[i], 32);
				// printf("*\n");
				k++;
			}
		}
		i++;
	}
	// printf("|%s|\n", map[0]);
	// printf("|%s|\n", map[1]);
	// printf("|%s|\n", map[2]);
	// printf("|%s|\n", map[3]);
	// printf("|%s|\n", map[4]);
	// printf("|%s|\n", map[5]);
	// exit(0);
}

char	**reFormeMap(char **map, t_infos *infos)
{
	infos->index_max_len = getBiggestLineIdex(map);
	infos->max_len = ft_strlen(map[infos->index_max_len]);
	makeitRectangle(map, infos->max_len);
	return (map);
}
// 11110111111111011100000010001
