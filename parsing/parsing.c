/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 21:17:31 by maneddam          #+#    #+#             */
/*   Updated: 2023/08/10 18:45:57 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void checkArg(char *mapPath)
{
	int fd;
	int i;

	fd = open(mapPath, O_RDONLY);
	if (fd < 0)
		printError("Map not found");
	i = 0;
	while (mapPath[i])
		i++;
	i--;
	if (mapPath[i] != 'b' || mapPath[--i] != 'u' || mapPath[--i] != 'c' || mapPath[--i] != '.')
		printError("Map extension must be as follow '.cub' !!");
}
void checkMapItems(char **map2d)
{
	int i;
	int j;

	i = 0;
	while (map2d[i])
	{
		j = 0;
		while (map2d[i][j])
		{
			if (map2d[i][j] != '1' && map2d[i][j] != '0' && map2d[i][j] != 32 && map2d[i][j] != '\t'
			&& map2d[i][j] != 'N' && map2d[i][j] != 'S' && map2d[i][j] != 'W' && map2d[i][j] != 'E')
			{
				printf("i) %d\n", i);
				printError("Invalid hh character");
			}
			j++;
		}
		i++;
	}
}

void getInfosCount(char *readLine, t_infos *infos)
{
	int i = 0;
	while (readLine[i] == 32 || readLine[i] == '\t')
		i++;
	if (readLine[i] == '\n')
		return;
	if (readLine[i] == 'N' && readLine[i + 1] == 'O')
		infos->infosArr[0] = "NO";
	else if (readLine[i] == 'S' && readLine[i + 1] == 'O')
		infos->infosArr[1] = "SO";
	else if (readLine[i] == 'W' && readLine[i + 1] == 'E')
		infos->infosArr[2] = "WE";
	else if (readLine[i] == 'E' && readLine[i + 1] == 'A')
		infos->infosArr[3] = "EA";
	else if (readLine[i] == 'F' && (readLine[i + 1] == '\0' || readLine[i + 1] == 32))
		infos->infosArr[4] = "F";
	else if (readLine[i] == 'C' && (readLine[i + 1] == '\0' || readLine[i + 1] == 32))
		infos->infosArr[5] = "C";
	// else
	// {
	// 	printf("%s\n", readLine);
	// 	printError("hahaha error");
	// }
}
void isAllInfosIn(t_infos *infos)
{
	int i = 0;
	while (i < 6)
	{
		if (ft_strcmp(infos->infosArr[i], "00") == 0)
			printError("Missing parameter");
		i++;
	}
	if (!infos->NO || !infos->SO || !infos->WE || !infos->EA || !infos->F || !infos->C)
		printError("Missing parameter");
	if (isCompound(infos))
		printError("Compound value");
}

void fillArrInfos(char *readline, t_infos *infos)
{
	static int linePos;
	int i;
	static bool done;


	i = 0;
	while (readline[i] == 32 || readline[i] == '\t')
		i++;
	if (readline[i] == 'N')
		getNord(readline, infos, i);
	else if (readline[i] == 'S')
		getSouth(readline, infos, i);
	else if (readline[i] == 'W')
		getWest(readline, infos, i);
	else if (readline[i] == 'E')
		getEast(readline, infos, i);
	else if (readline[i] == 'F')
		getFloor(readline, infos, i);
	else if (readline[i] == 'C')
		getCeiling(readline, infos, i);
	if (readline[i] == '1' && infos->parameters != 6)
		printError("Invalid order");
	if (readline[i] == '1' && infos->parameters == 6)
	{
		if (done == false)
		{
			infos->mapStartIndex = linePos;
			done = true;
		}
	}
	if (ft_strcmp(readline, "\n") != 0)
		linePos++;
}

void getFileElements(char *mapPath, t_infos *infos)
{
	char *map;
	char *fullMap = NULL;
	int fd;

	fd = open(mapPath, O_RDONLY);
	if (fd < 0)
		printError("Error opening file");

	map = get_next_line(fd);
	if (!map)
		printError("Invalid map");
	while (map != NULL)
	{
		fullMap = ft_strjoin_free(fullMap, map);
		getInfosCount(map, infos);
		fillArrInfos(map, infos);
		free(map);
		map = get_next_line(fd);
	}

	isAllInfosIn(infos);

	handleMap(fullMap, infos);
	checkMapItems(infos->map2d);
}

void parsing(char *argv, t_infos *infos)
{
	infos->p.x_startPos = 0;
	infos->p.y_startPos = 0;
	checkArg(argv);
	getFileElements(argv, infos);
	
}
