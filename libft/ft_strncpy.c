/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:36:24 by vlambert          #+#    #+#             */
/*   Updated: 2019/05/24 17:20:22 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (len--)
	{
		if (src[i])
		{
			dst[j] = src[i];
			i++;
		}
		j++;
	}
	dst[j] = 0;
	return (dst);
}
