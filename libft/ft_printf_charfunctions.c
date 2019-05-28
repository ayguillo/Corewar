/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charfunctions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 08:38:53 by vlambert          #+#    #+#             */
/*   Updated: 2019/02/20 10:41:45 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <stdlib.h>

char	*ft_wstr_to_str(wint_t *str, char *buf, t_options options, size_t *len)
{
	size_t	i;
	char	*t;

	i = 0;
	while (str && str[i] && (*len = ft_strlen(buf)) < (size_t)options.precision)
	{
		if (!(t = ft_putunicode(str[i])))
		{
			free(buf);
			return (NULL);
		}
		if (*len + ft_strlen(t) > (size_t)options.precision)
		{
			free(t);
			break ;
		}
		buf = ft_strjoinfree(buf, t);
		if (!(buf))
			return (NULL);
		i += 1;
	}
	return (buf);
}

char	*ft_prepare_char(char c, va_list ap, t_options *options, char *ch)
{
	char *buf;

	if (!(buf = ft_strnew(1)))
		return (NULL);
	if (c == 0)
		*ch = '%';
	if (c == 'c')
		*ch = (char)va_arg(ap, int);
	buf[0] = *ch;
	if (options->width && *ch == 0)
		options->width--;
	return (buf);
}

int		ft_ischarfunction(char c, va_list ap, t_options options)
{
	char	ch;
	char	*buf;

	ch = 0;
	if (((c == 'c' || c == 's') && options.length != 3) || c == 0)
	{
		if ((c == 0 || c == 'c')
				&& !(buf = ft_prepare_char(c, ap, &options, &ch)))
			return (-1);
		if (c == 's' && !(buf = va_arg(ap, char*)))
			buf = ft_strdup("(null)");
		else if (c == 's')
			buf = ft_strdup(buf);
		if (!buf)
			return (-1);
		if (c == 's')
			ft_strprec(buf, options);
		if (!(buf = ft_width(buf, options, 0)))
			return (-1);
		return (ft_strputfree(buf, c, ch, options));
	}
	return (0);
}

int		ft_iswcharfunction(char c, va_list ap, t_options options)
{
	char	*buf;
	size_t	len;
	wint_t	ch;

	len = 0;
	if ((c == 'c' && options.length == 3) || (c == 'C' && (options.length = 3)))
	{
		ch = va_arg(ap, wint_t);
		if (!ch)
		{
			if (!(buf = ft_strnew(0)))
				return (-1);
			if (options.width)
				options.width--;
		}
		if (ch && !(buf = ft_putunicode(ch)))
			return (-1);
		if (!(buf = ft_width(buf, options, 0)))
			return (-1);
		len = ft_strputfree(buf, c, ch, options);
	}
	return (len);
}

int		ft_iswstringfunction(char c, va_list ap, t_options options)
{
	char	*buf;
	wint_t	*str;
	size_t	len;

	len = 0;
	buf = NULL;
	if ((c == 's' && options.length == 3) || (c == 'S' && (options.length = 3)))
	{
		if (!(str = va_arg(ap, wint_t *)))
			buf = ft_strdup("(null)");
		else
			buf = ft_strnew(0);
		if (!buf || !(buf = ft_wstr_to_str(str, buf, options, &len))
				|| !(buf = ft_width(buf, options, 0)))
			return (-1);
		len = ft_strputfree(buf, c, 1, options);
	}
	return (len);
}
