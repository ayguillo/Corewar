/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpyfast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 11:13:33 by vlambert          #+#    #+#             */
/*   Updated: 2019/04/02 12:27:39 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	ft_strcpyfast(char *cpy, const char *s1, size_t i)
{
	while (i >= 8)
	{
		i -= 8;
		*(unsigned long long*)(cpy + i) = *(unsigned long long*)(s1 + i);
	}
	while (i--)
		cpy[i] = s1[i];
}
