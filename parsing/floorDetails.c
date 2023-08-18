/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorDetails.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 19:53:31 by maneddam          #+#    #+#             */
/*   Updated: 2023/08/09 15:06:27 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int getFsingleValue(char *readline)
{
	static int i;
	char *num;

	num = NULL;
	if (readline[i] == 'F' || readline[i] == 'C' || readline[i] == ',')
		i++;
	while (readline[i] == 32 || readline[i] == '\t')
		i++;
	while (readline[i] && readline[i] != ',' && readline[i] != '\n')
	{
		// printf("num : |%s|\n", num);
		num = ft_strjoin_char(num, readline[i]);
		i++;
	}
	// printf("->>				|%s|\n", num);
	if (ft_atoi(num) > 255 || ft_atoi(num) < 0)
		printError("Out of range");
	if (countWords(num) != 1)
		printError("Invalid value");

	return ft_atoi(num);
}

void handleFloorDetails(char *readLine, t_infos *infos)
{
	int i;

	i = 0;
	while (readLine[i] == 32 || readLine[i] == '\t')
		i++;
	readLine = readLine + i;

	countCommas(readLine);
	invalidCharacters(readLine);
	invalidForm(readLine);
	infos->F[0] = getFsingleValue(readLine);
	infos->F[1] = getFsingleValue(readLine);
	infos->F[2] = getFsingleValue(readLine);
	// printf("read : |%s|", readLine);
	// exit(0);
}
