/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 17:00:31 by vlambert          #+#    #+#             */
/*   Updated: 2019/03/14 09:57:37 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

int		ft_strputfree(char *buf, char c, int ch, t_options options)
{
	int		temp;

	if (!(temp = ft_strlen(buf)))
		temp = -1;
	if ((c == 'c' || c == 'C') && ch == 0)
	{
		if (!(options.less))
			ft_putstr(buf);
		ft_putchar(0);
		if (options.less)
			ft_putstr(buf);
		free(buf);
		if (temp == -1)
			return (1);
		return (temp + 1);
	}
	ft_putstr(buf);
	free(buf);
	return (temp);
}
