/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 08:39:15 by eej-jama          #+#    #+#             */
/*   Updated: 2023/08/26 08:39:22 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3d.h"

int rgb_to_hex(int red, int green, int blue)
{
    return (red << 16) | (green << 8) | blue;
}