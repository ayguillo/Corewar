/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dygouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 13:19:24 by dygouin           #+#    #+#             */
/*   Updated: 2019/01/30 10:46:44 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

void	ft_percentsplit(char *str, t_count a)
{
	while (a.i < a.len)
	{
		if (str[a.i] == '%')
			str[a.i] = 0;
		a.i += 1;
	}
}

void	ft_processstr(char *str, t_count *a, va_list ap, t_options *options)
{
	if (str[a->i])
	{
		ft_putstr(str + a->i);
		a->temp = ft_strlen(str + a->i);
		a->written += a->temp;
		a->i += a->temp;
	}
	if (a->i < a->len && !str[a->i])
		ft_percent(str, a, ap, options);
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	char		*str;
	t_count		a;
	t_options	options;

	if (!format || !(str = ft_strdup(format)))
		return (-1);
	a.len = ft_strlen(format);
	a.i = 0;
	a.written = 0;
	ft_percentsplit(str, a);
	va_start(ap, format);
	while (a.i < a.len)
		ft_processstr(str, &a, ap, &options);
	free(str);
	va_end(ap);
	return (a.written);
}
