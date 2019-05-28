/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putfloat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dygouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 17:48:11 by dygouin           #+#    #+#             */
/*   Updated: 2019/02/20 10:37:50 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	ft_negfloat(long double *c, char *buf)
{
	if (1.0 / *c < 0)
	{
		*c = -(*c);
		buf[0] = '-';
	}
}

char	*ft_getnum(char *buf, long double c, t_options options)
{
	options.number = (intmax_t)c;
	if (!(buf = ft_strjoinfree(buf, ft_ltoa_base(options, 10, 0))))
		return (NULL);
	return (buf);
}

char	*infnan(long double c, char *buf, int maj, t_options options)
{
	size_t	i;

	i = 0;
	if (c != c)
		buf = ft_strdup("nan");
	else if (c == 1.0 / 0.0)
	{
		if (options.plus)
			buf = ft_strdup("+inf");
		else if (options.space)
			buf = ft_strdup(" inf");
		else
			buf = ft_strdup("inf");
	}
	else if (c == -1.0 / 0.0)
		buf = ft_strdup("-inf");
	if (!(buf))
		return (NULL);
	while (maj && buf[i])
	{
		buf[i] = ft_toupper(buf[i]);
		i++;
	}
	return (buf);
}

char	*ft_getfloat(long double c, char *buf, t_options options)
{
	size_t	i;

	i = 0;
	while (c > 9223372036854775807.0 && (c /= 10))
		i++;
	options.length = 7;
	if (!(buf = ft_getnum(buf, c, options)))
		return (NULL);
	while (i--)
	{
		if (!(buf = ft_getnum(buf, c, options)))
			return (NULL);
		c = (c - (intmax_t)c) * 10;
		if (i == 0)
			c = 0;
	}
	return (buf);
}

int		ft_putfloat(long double c, t_options options, int maj)
{
	char		*buf;

	buf = NULL;
	if (c != c || c == 1.0 / 0.0 || c == -1.0 / 0.0)
	{
		if (!(buf = infnan(c, buf, maj, options)))
			return (-1);
	}
	else
	{
		if (!(buf = ft_strnew(1)))
			return (-1);
		ft_negfloat(&c, buf);
		if (!(buf = ft_getfloat(c, buf, options)))
			return (-1);
		if (!(buf = ft_floatprec(buf, options, c))
				|| !(buf = ft_plusspace(buf, options)))
			return (-1);
	}
	if (!(buf = ft_width(buf, options, 1)))
		return (-1);
	return (ft_strputfree(buf, 'f', 1, options));
}
