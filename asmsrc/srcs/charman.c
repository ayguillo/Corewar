/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charman.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 14:05:37 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/04 16:52:10 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

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

int		ft_strclentab(const char *s1, char c)
{
	int	i;
	int	ret;

	i = -1;
	ret = 0;
	while (s1[++i] || s1[i] == c)
	{
		if (s1[i] == '\t' || s1[i] == ' ')
			ft_dprintf(2, "%c", s1[i]);
		else
			ret++;
	}
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
