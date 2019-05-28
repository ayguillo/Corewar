/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 13:18:10 by vlambert          #+#    #+#             */
/*   Updated: 2018/11/29 14:11:24 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int i;

	i = 0;
	while (len--)
	{
		if (!(dst <= src + len && dst >= src))
		{
			((unsigned char*)dst)[i] = ((unsigned char*)src)[i];
			i++;
		}
		if (dst <= src + len && dst >= src)
			((unsigned char*)dst)[len] = ((unsigned char*)src)[len];
	}
	return (dst);
}
