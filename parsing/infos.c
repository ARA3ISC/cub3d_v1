/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 21:17:24 by maneddam          #+#    #+#             */
/*   Updated: 2023/08/09 15:08:47 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	getNord(char *readLine, t_infos *infos, int pos)
{
	static int duplicated;
	int i;

	i = pos;
	if ((readLine[pos + 2] != 32 && readLine[pos + 2] != '\t'))
		printError("Invalid form");
	if (!duplicated)
	{
		duplicated = 1;
		// i = 0;
		infos->NO = NULL;
		i = i + 2;
		while(readLine[i] == 32 || readLine[i] == '\t')
			i++;
		while (readLine[i] && readLine[i] != '\n')
		{
			infos->NO = ft_strjoin_char(infos->NO, readLine[i]);
			i++;
		}
		infos->parameters++;
	}
	else
		printError("Duplicated parameter");

}

void	getSouth(char *readLine, t_infos *infos, int pos)
{
	int i;
	static int duplicated;

	i = pos;
	if ((readLine[pos + 2] != 32 && readLine[pos + 2] != '\t'))
		printError("Invalid form");
	if (!duplicated)
	{
		duplicated = 1;
		infos->SO = NULL;
		i = i + 2;
		while(readLine[i] == 32 || readLine[i] == '\t')
			i++;
		while (readLine[i] && readLine[i] != '\n')
		{
			infos->SO = ft_strjoin_char(infos->SO, readLine[i]);
			i++;
		}
		infos->parameters++;
	}
	else
		printError("Duplicated parameter");
}
void	getWest(char *readLine, t_infos *infos, int pos)
{
	static int duplicated;
	int i;

	i = pos;
	if ((readLine[pos + 2] != 32 && readLine[pos + 2] != '\t'))
		printError("Invalid form");
	if (!duplicated)
	{
		duplicated = 1;
		// i = 0;
		infos->WE = NULL;

		i = i + 2;
		while(readLine[i] == 32 || readLine[i] == '\t')
			i++;
		while (readLine[i] && readLine[i] != '\n')
		{
			infos->WE = ft_strjoin_char(infos->WE, readLine[i]);
			i++;
		}
		infos->parameters++;
	}
	else
		printError("Duplicated parameter");
}

void	getEast(char *readLine, t_infos *infos, int pos)
{
	static int duplicated;
	int i;

	i = pos;
	if ((readLine[pos + 2] != 32 && readLine[pos + 2] != '\t'))
		printError("Invalid form");
	if (!duplicated)
	{
		duplicated = 1;
		// i = 0;
		infos->EA = NULL;

		i = i + 2;
		while(readLine[i] == 32 || readLine[i] == '\t')
			i++;
		while (readLine[i] && readLine[i] != '\n')
		{
			infos->EA = ft_strjoin_char(infos->EA, readLine[i]);
			i++;
		}
		infos->parameters++;
	}
	else
		printError("Duplicated parameter");
}

// ! baqee
void	getFloor(char *readLine, t_infos *infos, int pos)
{
	infos->F = malloc(3 * sizeof(int));
	if ((readLine[pos + 1] != 32 && readLine[pos + 1] != '\t'))
		printError("Invalid form");
	handleFloorDetails(readLine, infos);
	infos->parameters++;
}

// ! baqee
void	getCeiling(char *readLine, t_infos *infos, int pos)
{
	infos->C = malloc(3 * sizeof(int));
	if ((readLine[pos + 1] != 32 && readLine[pos + 1] != '\t'))
		printError("Invalid form");

	handleCeilingDetails(readLine, infos);
	infos->parameters++;
}

