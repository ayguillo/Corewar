/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otherfunctions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 14:46:21 by vlambert          #+#    #+#             */
/*   Updated: 2019/02/20 10:39:42 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int		ft_isnfunction(char c, va_list ap, t_count a)
{
	int		*written;

	if (c == 'n')
	{
		written = va_arg(ap, int*);
		if (written)
			*written = a.written;
		return (-1);
	}
	return (0);
}

int		ft_ispointfunction(char c, va_list ap, t_options options)
{
	char	*buf;
	int		maj;

	if (c == 'p' || c == 'P')
	{
		options.length = 3;
		options.hashtag = 1;
		options.number = (intmax_t)va_arg(ap, void*);
		maj = (c == 'p') ? 0 : 1;
		if (!(buf = ft_ltoa_base(options, 16, maj)))
			return (-1);
		if (!(options.precision))
			buf[0] = 0;
		if (!(buf = ft_nbrprec(buf, options)))
			return (-1);
		options.number = 1;
		if (!(buf = ft_hashtag(buf, options, 16, maj))
				|| !(buf = ft_width(buf, options, 1)))
			return (-1);
		return (ft_strputfree(buf, c, 1, options));
	}
	return (0);
}

int		ft_iscolorfunction(char c, va_list ap)
{
	char	*color;

	if (c == 'r')
	{
		color = va_arg(ap, char*);
		if (color && color[0] == '\033')
			ft_putstr(color);
		return (-1);
	}
	return (0);
}
