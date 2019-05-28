/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:09:09 by vlambert          #+#    #+#             */
/*   Updated: 2019/04/02 11:36:08 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*cpy;

	i = ft_strlen(s1);
	cpy = 0;
	if (!(cpy = (char*)malloc((i + 1) * sizeof(char))))
		return (NULL);
	cpy[i] = 0;
	ft_strcpyfast(cpy, s1, i);
	return (cpy);
}
