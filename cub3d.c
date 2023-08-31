/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 21:17:42 by maneddam          #+#    #+#             */
/*   Updated: 2023/08/30 23:53:24 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_infos	infos;
	int		i;

	infos.parameters = 0;
	infos.max_len = 0;
	infos.index_max_len = 0;

	i = 0;
	while (i < 6)
	{
		infos.infosArr[i] = malloc(3);
		infos.infosArr[i] = "00";
		i++;
	}
	if (argc == 2)
	{
		parsing(argv[1], &infos);
		raycasting(&infos);
		printf("theres is %d\n", infos.parameters);
		// printf("NO : %s*\n", infos.NO);
		// printf("SO : %s*\n", infos.SO);
		// printf("WE : %s*\n", infos.WE);
		// printf("EA : %s*\n", infos.EA);
		// printf("F : %x*\n", rgb_to_hex(infos.F[0], infos.F[1], infos.F[2]));
		// printf("C : %x*\n", rgb_to_hex(infos.C[0], infos.C[1], infos.C[2]));
	}
	else
		printError("Invalid argument number");
}
