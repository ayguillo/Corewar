/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 12:23:33 by vlambert          #+#    #+#             */
/*   Updated: 2019/02/20 10:40:48 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <stdlib.h>

char	*ft_newfull(unsigned int len, t_options options)
{
	char	c;
	char	*str;

	str = NULL;
	if (!(str = ft_strnew(len)))
		return (str);
	if (options.zero && !(options.less))
		c = '0';
	else
		c = ' ';
	while (len-- > 0)
		str[len] = c;
	return (str);
}

void	ft_declaration(char *buf, int i, int j)
{
	buf[j] = buf[i];
	buf[i] = '0';
}

char	*ft_width(char *buf, t_options options, int isnumber)
{
	int		i;
	char	*str;

	if (options.width > 0 && options.width > (signed)ft_strlen(buf))
	{
		if (!(str = ft_newfull(options.width - ft_strlen(buf), options)))
		{
			free(buf);
			return (NULL);
		}
		if ((!(options.less) && !(buf = ft_strjoinfree(str, buf)))
				|| (options.less && !(buf = ft_strjoinfree(buf, str))))
			return (NULL);
		i = -1;
		while (isnumber && options.zero && !(options.less) && buf[++i])
		{
			if (buf[i] == '+' || buf[i] == '-' || buf[i] == ' ')
				ft_declaration(buf, i, 0);
			if (buf[i] == 'x' || buf[i] == 'X')
				ft_declaration(buf, i, 1);
		}
	}
	return (buf);
}

int		ft_iswidth(char *str, va_list ap, t_options *options)
{
	int		ret;

	ret = -1;
	if (*str == '*')
	{
		ret = va_arg(ap, int);
		if (ret < 0)
		{
			ret = -ret;
			options->less = 1;
		}
	}
	if (*str >= '0' && *str <= '9')
		ret = ft_atoi(str);
	if (ret < 0 && (*str == '*' || ft_isdigit(*str)))
		ret = 0;
	return (ret);
}

void	ft_getwidth(char *str, t_count *a, va_list ap, t_options *options)
{
	if (ft_isdigit(str[a->i]) || str[a->i] == '*')
	{
		if (ft_isdigit(str[a->i]))
		{
			a->width1 = ft_iswidth(str + a->i, ap, options);
			if (a->width1 > options->width || options->width == a->width2)
				options->width = a->width1;
		}
		if (str[a->i] == '*')
		{
			a->width2 = ft_iswidth(str + a->i, ap, options);
			if (a->width2 > options->width || options->width == a->width1)
				options->width = a->width2;
		}
		if (str[a->i] != '*')
		{
			while (ft_isdigit(str[a->i + 1]))
				a->i += 1;
		}
	}
}
