/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 13:18:51 by vlambert          #+#    #+#             */
/*   Updated: 2019/01/30 10:44:45 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <stdlib.h>

char	*ft_plusspace(char *buf, t_options options)
{
	char	*to_free;

	if (options.plus && buf[0] != '-')
	{
		to_free = buf;
		buf = ft_strjoin("+", buf);
		free(to_free);
	}
	if (options.space && buf[0] != '+' && buf[0] != '-')
	{
		to_free = buf;
		buf = ft_strjoin(" ", buf);
		free(to_free);
	}
	return (buf);
}

char	*ft_hashtag(char *buf, t_options options, char base, char maj)
{
	char	*hash;

	if (options.hashtag && (((base == 8 && buf[0] != '0')
					|| base == 16) && options.number != 0))
	{
		if (!(hash = ft_strnew(2)))
			return (NULL);
		hash[0] = '0';
		if (base == 16 && !maj)
			hash[1] = 'x';
		if (base == 16 && maj)
			hash[1] = 'X';
		if (!(buf = ft_strjoinfree(hash, buf)))
			return (NULL);
	}
	if (options.hashtag && base == 10 && !(ft_strchr(buf, '.')))
	{
		hash = buf;
		buf = ft_strjoin(buf, ".");
		free(hash);
	}
	return (buf);
}
