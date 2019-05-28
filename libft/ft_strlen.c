/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:03:10 by vlambert          #+#    #+#             */
/*   Updated: 2019/05/24 17:10:26 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlen(const char *s)
{
	unsigned short	*u;
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	if (s && s[i])
		u = (unsigned short*)s;
	while (s && s[i])
	{
		if (!(u[j] & 0xff00))
			return (i + 1);
		if (!(s[i + 2]))
			return (i + 2);
		if (!(u[j + 1] & 0xff00))
			return (i + 3);
		i += 4;
		j += 2;
	}
	return (i);
}
