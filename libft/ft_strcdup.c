/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 11:18:20 by ayguillo          #+#    #+#             */
/*   Updated: 2019/03/22 14:46:24 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strcdup(const char *s1, char c, int *i)
{
	char	*dup;
	int		n;

	if (!s1)
		return (NULL);
	*i = ft_strclen(s1, c);
	if (!(dup = (char*)malloc(sizeof(char) * (*i + 1))))
		return (0);
	n = 0;
	while (s1[n] && s1[n] != c)
	{
		dup[n] = s1[n];
		n++;
	}
	dup[n] = '\0';
	return (dup);
}
