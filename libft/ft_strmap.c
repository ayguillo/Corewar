/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 14:03:36 by vlambert          #+#    #+#             */
/*   Updated: 2018/11/29 14:23:44 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	size;
	char	*s2;
	size_t	i;

	if (!s || !f)
		return (NULL);
	size = ft_strlen(s);
	if (!(s2 = ft_strnew(size)))
		return (NULL);
	i = 0;
	while (*s)
		s2[i++] = (*f)(*(s++));
	return (s2);
}
