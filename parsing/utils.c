/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 21:17:37 by maneddam          #+#    #+#             */
/*   Updated: 2023/08/09 15:14:54 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int countWords(char *str)
{
	int count;
	int i;
	bool inWord;

	inWord = false;
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
		{
			inWord = false;
		}
		else if (!inWord)
		{
			inWord = true;
			count++;
		}
		i++;
	}
	return count;
}

bool isCompound(t_infos *infos)
{
	if (countWords(infos->NO) > 1 || countWords(infos->SO) > 1 || countWords(infos->WE) > 1 || countWords(infos->EA) > 1)
		return true;
	return false;
}

void countCommas(char *readLine)
{
	int count;
	int i;

	count = 0;
	i = 0;
	if (readLine[i] != 'F' && readLine[i] != 'C')
		return;

	while (readLine[i])
	{
		if ((readLine[i]) == ',')
			count++;
		i++;
	}
	if (count != 2)
		printError("Invalid commas count");
}

void invalidCharacters(char *readline)
{
	int i;

	i = 0;
	while (readline[i] == 32 || readline[i] == '\t')
		i++;
	i++;
	while (readline[i])
	{
		if (readline[i] != ',' && !ft_isdigit(readline[i]) && readline[i] != '\n' && readline[i] != 32
			&& readline[i] != '\t')
			printError("Invalid character");
		i++;
	}
}

void invalidForm(char *readLine)
{
	int i;
	bool isComma;

	i = 0;
	isComma = false;
	while (readLine[i])
	{
		if (readLine[i] == ',')
		{
			if (readLine[i + 1])
				i++;
			while (readLine[i] == 32 || readLine[i] == '\t')
				i++;
			if (readLine[i] == ',')
				isComma = true;
			else
				isComma = false;
			if (isComma)
				printError("Comma after comma");
		}
		i++;
	}
}
