/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charman.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 14:05:37 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/05 14:58:08 by ayguillo         ###   ########.fr       */
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

int		ft_strclentab(const char *s1, char c, char print)
{
	int	i;
	int	ret;
	int	j;

	i = -1;
	ret = 0;
	while (s1[++i] && s1[i] != c)
	{
		if ((s1[i] == '\t' || s1[i] == ' '))
			ft_dprintf(2, "%c", s1[i]);
		else if (print)
		{
			j = -1;
			while (LABEL_CHARS[++j])
				if (LABEL_CHARS[j] == s1[i])
					break ;
			if (LABEL_CHARS[j] != '\0')
				ft_dprintf(2, "%c", print);
		}
		else
			ret++;
	}
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
