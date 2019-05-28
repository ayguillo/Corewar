/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 09:23:43 by vlambert          #+#    #+#             */
/*   Updated: 2019/02/20 10:35:13 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int		ft_isflags(char *str, t_options *options)
{
	if (*str == '-')
		options->less = 1;
	else if (*str == '+')
		options->plus = 1;
	else if (*str == ' ')
		options->space = 1;
	else if (*str == '#')
		options->hashtag = 1;
	else if (*str == '0')
		options->zero = 1;
	else
		return (0);
	return (1);
}

int		ft_isprecision(char *str, va_list ap)
{
	int		ret;

	ret = -1;
	if (str[0] == '.')
	{
		if (str[1] == '*')
			ret = va_arg(ap, int);
		else if (str[1] >= '0' && str[1] <= '9')
			ret = ft_atoi(str + 1);
		else
			ret = 0;
	}
	if (ret < -1)
		ret = -1;
	return (ret);
}

int		ft_islength(char *str)
{
	if (str[0] == 'h')
	{
		if (str[1] == 'h')
			return (1);
		return (2);
	}
	if (str[0] == 'l')
	{
		if (str[1] == 'l')
			return (4);
		return (3);
	}
	if (str[0] == 'z')
		return (5);
	if (str[0] == 'L')
		return (6);
	if (str[0] == 'j')
		return (7);
	return (0);
}

int		ft_isforprintf(char c)
{
	if (c == ' ' || c == '#' || c == '+' || c == '-' || c == '*'
			|| c == '.' || c == 'h' || c == 'l' || c == 'j' || c == 'z'
			|| c == 'L')
		return (1);
	return (0);
}

void	ft_getargs(char *str, t_count *a, va_list ap, t_options *options)
{
	while (a->i < a->len && (ft_isdigit(str[a->i])
				|| ft_isforprintf(str[a->i])))
	{
		ft_isflags(str + a->i, options);
		ft_getwidth(str, a, ap, options);
		if (options->precision == -1 && str[a->i] == '.')
		{
			options->precision = ft_isprecision(str + a->i, ap);
			if (str[a->i] == '.' && (str[a->i + 1] == '*'
						|| ft_isdigit(str[a->i + 1])))
				a->i += 1;
			while (ft_isdigit(str[a->i + 1]))
				a->i += 1;
		}
		if (options->length < ft_islength(str + a->i))
		{
			options->length = ft_islength(str + a->i);
			if (options->length == 4 || options->length == 1)
				a->i += 1;
		}
		a->i += 1;
	}
}
