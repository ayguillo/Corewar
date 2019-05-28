/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 13:44:24 by vlambert          #+#    #+#             */
/*   Updated: 2019/02/20 10:42:11 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include <stdlib.h>

void	ft_init_options(t_options *options)
{
	options->plus = 0;
	options->less = 0;
	options->space = 0;
	options->hashtag = 0;
	options->zero = 0;
	options->width = 0;
	options->unsign = 0;
	options->precision = -1;
	options->length = 0;
	options->number = 0;
	options->doubl = 0.0;
}

void	ft_bad_specifier(char *str, t_count *a, t_options *options)
{
	char	*buf;

	if (str[a->i] && options->width)
		options->width -= 1;
	buf = ft_newfull(options->width, *options);
	if (buf)
	{
		if (!options->less)
			ft_putstr(buf);
		if (str[a->i])
		{
			a->temp = ft_strlen(buf) + 1;
			ft_putchar(str[a->i]);
			a->i += 1;
		}
		else
			a->temp = ft_strlen(buf);
		if (options->less)
			ft_putstr(buf);
		free(buf);
	}
}

void	ft_percent(char *str, t_count *a, va_list ap, t_options *options)
{
	ft_init_options(options);
	a->i += 1;
	ft_getargs(str, a, ap, options);
	a->temp = 0;
	if (a->i < a->len
			&& ((a->temp = ft_isintfunction(str[a->i], ap, options))
			|| (a->temp = ft_ischarfunction(str[a->i], ap, *options))
			|| (a->temp = ft_isfloatfunction(str[a->i], ap, *options))
			|| (a->temp = ft_ispointfunction(str[a->i], ap, *options))
			|| (a->temp = ft_iswstringfunction(str[a->i], ap, *options))
			|| (a->temp = ft_iswcharfunction(str[a->i], ap, *options))
			|| (a->temp = ft_isnfunction(str[a->i], ap, *a))
			|| (a->temp = ft_iscolorfunction(str[a->i], ap))))
		a->i += 1;
	else if (options->width)
		ft_bad_specifier(str, a, options);
	if (a->temp > 0)
		a->written += a->temp;
}
