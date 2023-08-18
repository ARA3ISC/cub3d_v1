/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 21:17:08 by maneddam          #+#    #+#             */
/*   Updated: 2023/08/09 15:05:24 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// !header file needed

void	printError(char *msg)
{
	printf(RED"Error\n%s"RESET, msg);
	exit(EXIT_FAILURE);
}


