/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunicode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dygouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 13:18:59 by dygouin           #+#    #+#             */
/*   Updated: 2019/01/30 10:48:00 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	ft_mask(int i, char *str, wint_t num)
{
	int j;

	j = i;
	while (i > 0)
	{
		str[i--] = ((char)(num) | 0x80) & 0xbf;
		num = num >> 6;
	}
	if (j == 1)
		str[0] = ((char)num | 0xC0) & 0xdf;
	if (j == 2)
		str[0] = ((char)num | 0xe0) & 0xef;
	if (j == 3)
		str[0] = ((char)num | 0xf0) & 0xf7;
}

char	*ft_putunicode(wint_t num)
{
	char	*str;

	str = NULL;
	if (!(str = ft_strnew(4)))
		return (NULL);
	if (num > 0 && num <= 0x7f)
		str[0] = (char)(num & 0x7f);
	else if (num <= 0x7ff)
		ft_mask(1, str, num);
	else if (num <= 0xffff)
	{
		if (num >= 0xd800 && num <= 0xdfff)
			return (NULL);
		ft_mask(2, str, num);
	}
	else if (num <= 0x10ffff)
	{
		if (num > 0x2ffff && num < 0xe0000)
			return (ft_strdup(""));
		ft_mask(3, str, num);
	}
	return (str);
}
