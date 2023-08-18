/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 09:04:27 by gloukas           #+#    #+#             */
/*   Updated: 2023/08/04 22:48:01 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_new(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

// int	ft_strlen(char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }

// char	*ft_strdup(char *src)
// {
// 	char	*t;
// 	int		i;

// 	i = 0;
// 	t = malloc(ft_strlen(src) + 1);
// 	if (!t)
// 		return (NULL);
// 	while (src[i])
// 	{
// 		t[i] = src[i];
// 		i++;
// 	}
// 	t[i] = '\0';
// 	return (t);
// }

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*new_s;
	int		i;
	int		c;

	i = 0;
	c = 0;
	if (!s1)
		return ft_strdup(s2);
	new_s = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new_s)
		return (free(s1), NULL);
	while (s1[i])
		new_s[c++] = s1[i++];
	i = 0;
	while (s2[i])
		new_s[c++] = s2[i++];
	new_s[c] = '\0';
	return (free(s1), new_s);
}

// char	*ft_strchr(char *s, int find)
// {
// 	while (s && *s)
// 	{
// 		if (*s == (char)find)
// 			return (s);
// 		s++;
// 	}
// 	return (NULL);
// }
