/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charman.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 14:05:37 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/19 14:37:11 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/asm.h"

int		ft_diffis(const char *s1, const char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	return (i);
}

int			ft_strclentab(const char *s1, char print, char *str, int occ)
{
	int	ret;
	int	j;
	int	i;
	int	k;

	ret = 0;
	if (!print)
	{
		while (s1 && *s1)
		{
			if (*s1 == '\t')
				ret += 8 - (ret % 8);
			else
				ret++;
			if (*s1 == SEPARATOR_CHAR)
				--occ;
			++s1;
			if (occ == 0)
				break ;
		}
	}
	while (s1 && *s1 && s1 != str)
	{
		if (*s1 == '\t' && !print)
			ret += 8 - (ret % 8);
		else if (print)
		{
			i = 0;
			j = 0;
			while (*s1 && (*s1 == '\t' || *s1 == ' '))
			{
				if (*s1 == '\t')
				{
					k = 8 - (j % 8);
					j += k;
					while (k-- > 0)
						ft_dprintf(2, " ");
				}
				else
				{
					ft_dprintf(2, " ");
					j++;
				}
				i++;
				++s1;
			}
			while (*s1)
			{
				i = 0;
				j = 0;
				while (LABEL_CHARS[i])
				{
					if (LABEL_CHARS[i] == *s1)
						j = 1;
					if (j == 0)
						break;
					i++;
				}
				ft_dprintf(2, "%c", print);
				if (j == 0)
					break;
				++s1;
			}
		}
		else
			ret++;
		++s1;
	}
	if (ret)
		ret++;
	return (ret);
}

void	ft_strprintspaces(const char *s1)
{
	int		i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] == ' ' || s1[i] == '\t')
			ft_dprintf(2, "%c", s1[i]);
		else
			break;
		i++;
	}
}

int		ft_passtab(char *line, int *i, int ret)
{
	if (line[*i] == '\t')
		ret += 8 - (ret % 8);
	else
		ret++;
	(*i)++;
	return (ret);
}
