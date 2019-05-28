/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dygouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 12:59:54 by dygouin           #+#    #+#             */
/*   Updated: 2019/01/30 10:47:49 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int						ft_getlen(char base, uintmax_t *val, t_options options)
{
	int					i;
	uintmax_t			multiple;

	i = 1;
	if (options.number < 0 && base == 10 && !options.unsign)
	{
		*val = options.number * -1;
		i = 2;
	}
	else
		*val = (uintmax_t)options.number;
	options.length == 0 ? *val = (unsigned int)(*val) : 0;
	options.length == 1 ? *val = (unsigned char)(*val) : 0;
	options.length == 2 ? *val = (unsigned short int)(*val) : 0;
	options.length == 3 ? *val = (unsigned long int)*(val) : 0;
	options.length == 4 ? *val = (unsigned long long int)*(val) : 0;
	options.length == 5 ? *val = (size_t)(*val) : 0;
	multiple = *val;
	while (multiple >= (uintmax_t)base)
	{
		multiple = multiple / base;
		i++;
	}
	return (i);
}

void					ft_filltab(char tab[17], char maj)
{
	int					i;
	char				j;
	char				k;

	i = 0;
	j = '0';
	k = 'a';
	while (j != ':')
		tab[i++] = j++;
	while (maj == 0 && k != 'g')
		tab[i++] = k++;
	while (maj == 1 && k - 32 != 'G')
		tab[i++] = (k++ - 32);
}

char					*ft_ltoa_base(t_options options, char base, char maj)
{
	char		tab[17];
	int			len;
	char		*sol;
	uintmax_t	val;

	tab[16] = '\0';
	if (base > 16 || base <= 1)
		return (NULL);
	ft_filltab(tab, maj);
	len = ft_getlen(base, &val, options);
	if (!(sol = ft_strnew(len)))
		return (NULL);
	if (options.number < 0 && base == 10 && !options.unsign)
	{
		val = options.number * -1;
		sol[0] = '-';
	}
	while (len-- > 0 && sol[len] != '-' && sol[len] != '+')
	{
		sol[len] = tab[val % base];
		val /= base;
	}
	return (sol);
}
