/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbrfunctions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 08:38:53 by vlambert          #+#    #+#             */
/*   Updated: 2019/03/07 14:24:46 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_getnumber(va_list ap, t_options *options)
{
	if (options->length == 0)
		options->number = va_arg(ap, int);
	else if (options->length == 1)
		options->number = (char)va_arg(ap, int);
	else if (options->length == 2)
		options->number = (short)va_arg(ap, int);
	else if (options->length == 3)
		options->number = va_arg(ap, long);
	else if (options->length == 4)
		options->number = va_arg(ap, long long);
	else if (options->length == 5)
		options->number = va_arg(ap, size_t);
	else if (options->length == 7)
		options->number = va_arg(ap, intmax_t);
	else
		return (0);
	return (1);
}

static char	*ft_prepare_number(char c, va_list ap, t_options *options)
{
	char	maj;
	char	base;
	char	*buf;

	maj = (c == 'X') ? 1 : 0;
	buf = NULL;
	ft_getnumber(ap, options);
	options->unsign = (c == 'u') ? 1 : 0;
	if (((c == 'd' || c == 'i' || c == 'u') && (base = 10))
			|| (c == 'o' && (base = 8))
			|| ((c == 'x' || c == 'X') && (base = 16))
			|| (c == 'b' && (base = 2)))
		buf = ft_ltoa_base(*options, base, maj);
	if (!buf)
		return (NULL);
	if (options->less || options->precision != -1)
		options->zero = 0;
	if (!options->precision && buf[0] == '0'
			&& !buf[1] && !(options->hashtag && base == 8))
		buf[0] = 0;
	if (!(buf = ft_nbrprec(buf, *options)) || (base != 10
				&& !(buf = ft_hashtag(buf, *options, base, maj)))
			|| ((c == 'd' || c == 'i') && !(buf = ft_plusspace(buf, *options))))
		return (NULL);
	return (buf);
}

int			ft_isintfunction(char c, va_list ap, t_options *options)
{
	char	*buf;

	if (c == 'U' || c == 'D' || c == 'I' || c == 'O' || c == 'B')
	{
		c += 'a' - 'A';
		options->length = 3;
	}
	if (c == 'd' || c == 'i' || c == 'u' || c == 'o'
			|| c == 'x' || c == 'X' || c == 'b')
	{
		if (!(buf = ft_prepare_number(c, ap, options)))
			return (-1);
		if (c == 'd' && options->width && options->zero
				&& options->precision >= 0)
			options->zero = 0;
		if (!(buf = ft_width(buf, *options, 1)))
			return (-1);
		return (ft_strputfree(buf, c, 1, *options));
	}
	return (0);
}

int			ft_isfloatfunction(char c, va_list ap, t_options options)
{
	int		temp;

	if (c == 'f' || c == 'F')
	{
		if (options.length != 6)
			temp = ft_putfloat(va_arg(ap, double), options, (c == 'F'));
		if (options.length == 6)
			temp = ft_putfloat(va_arg(ap, long double), options, (c == 'F'));
		return (temp);
	}
	return (0);
}
