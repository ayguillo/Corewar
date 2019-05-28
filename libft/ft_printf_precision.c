/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 12:10:59 by vlambert          #+#    #+#             */
/*   Updated: 2019/02/20 10:43:21 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <stdlib.h>

static int	ft_overnine(char **buf, int i)
{
	int		len;
	char	swap;
	char	*to_free;

	to_free = *buf;
	if ((*buf = ft_strjoin(*buf, "1")))
		return (0);
	free(to_free);
	len = ft_strlen(*buf) - 1;
	while (i < len)
	{
		swap = (*buf)[i];
		buf[0][i] = buf[0][len];
		buf[0][len] = swap;
		i++;
	}
	return (1);
}

static int	ft_round(long double c, char **buf)
{
	int		i;

	if (((long long)c % 2 && c - (long long)c >= 0.5)
			|| (!((long long)c % 2) && c - (long long)c > 0.5))
	{
		i = 0;
		while (buf[0][i])
			i++;
		if (i - 1 >= 0 && buf[0][i - 1] == '.')
			i--;
		while (--i >= 0 && buf[0][i] == '9')
		{
			buf[0][i] = '0';
			if (buf[0][i - 1] == '.')
				i--;
		}
		if (i >= 0 && ft_isdigit(buf[0][i]))
			buf[0][i] += 1;
		else
		{
			if (!(ft_overnine(buf, i)))
				return (0);
		}
	}
	return (1);
}

char		*ft_floatprec(char *buf, t_options options, long double c)
{
	unsigned int	i;

	if (options.precision != 0 || options.hashtag)
	{
		buf = ft_strjoinfree(buf, ft_strdup("."));
		if (!(buf))
			return (NULL);
		if (options.precision == -1)
			options.precision = 6;
		i = options.precision;
		while (i--)
		{
			c = (c - (long long)c) * 10;
			options.number = (long long)c;
			if (!(buf = ft_strjoinfree(buf, ft_ltoa_base(options, 10, 0))))
				return (NULL);
		}
	}
	ft_round(c, &buf);
	return (buf);
}

void		ft_strprec(char *buf, t_options options)
{
	if (options.precision > -1
			&& (unsigned)options.precision < ft_strlen(buf))
		buf[options.precision] = 0;
}

char		*ft_nbrprec(char *buf, t_options options)
{
	if (options.precision == -1)
		options.precision = 0;
	options.width = options.precision;
	if (buf[0] == '-' || buf[0] == '+' || buf[0] == ' ')
		options.width += 1;
	options.zero = 1;
	options.less = 0;
	return (ft_width(buf, options, 1));
}
