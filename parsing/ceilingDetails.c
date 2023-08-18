/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceilingDetails.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 10:37:36 by maneddam          #+#    #+#             */
/*   Updated: 2023/08/09 15:06:16 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int getCsingleValue(char *readline)
{
	static int i;
	char *num;

	num = NULL;
	// exit(0);
	if (readline[i] == 'F' || readline[i] == 'C' || readline[i] == ',')
		i++;
	while (readline[i] == 32 || readline[i] == '\t')
		i++;
	while (readline[i] && readline[i] != ',' && readline[i] != '\n')
	{
		num = ft_strjoin_char(num, readline[i]);
		i++;
	}
	if (ft_atoi(num) > 255 || ft_atoi(num) < 0)
		printError("Out of range");
	// printf("num : |%s|\n", num);
	if (countWords(num) != 1)
		printError("Invalid value");
	// free(num);
	return ft_atoi(num);
}

void handleCeilingDetails(char *readLine, t_infos *infos)
{
	int i;

	i = 0;
	while (readLine[i] == 32 || readLine[i] == '\t')
		i++;
	readLine = readLine + i;

	// printf("readline : |%s|\n", readLine);
	// exit(0);


	countCommas(readLine);
	invalidCharacters(readLine);
	invalidForm(readLine);
	infos->C[0] = getCsingleValue(readLine);
	infos->C[1] = getCsingleValue(readLine);
	infos->C[2] = getCsingleValue(readLine);
	// printf("read : |%s|", readLine);
}
