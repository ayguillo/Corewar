/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 10:55:17 by vlambert          #+#    #+#             */
/*   Updated: 2018/11/29 14:32:58 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <unistd.h>

static size_t	ft_fill(char *buff, size_t i, int n)
{
	int		multiple;
	int		negat;

	negat = 1;
	multiple = 1000000000;
	if (n < 0)
	{
		negat = -1;
		buff[i++] = '-';
	}
	while (!(n / multiple))
		multiple /= 10;
	while (multiple)
	{
		buff[i++] = n / multiple * negat + '0';
		n %= multiple;
		multiple /= 10;
	}
	return (i);
}

void			ft_putnbr_fd(int n, int fd)
{
	size_t	i;
	char	buff[12];

	i = 0;
	if (n == 0)
		buff[i++] = '0';
	else
		i = ft_fill(buff, i, n);
	buff[i] = 0;
	write(fd, buff, ft_strlen(buff));
}
