/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingseparator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 12:04:50 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/10 10:36:47 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../includes/op.h"
#include "../libft/libft.h"
#include <stdlib.h>

static int		ft_islab(char *spaces, int *i, t_gnl *gnl)
{
	int	j;

	(*i)++;
	while (spaces[*i] && spaces[*i] != SEPARATOR_CHAR)
	{
		j = -1;
		while (LABEL_CHARS[++j])
			if (spaces[*i] == LABEL_CHARS[j])
				break;
		if (LABEL_CHARS[j] == '\0')
			return (ft_syntax(NULL, 3, gnl, spaces[*i]));
		(*i)++;
	}
	return (1);
}

static int		ft_isdir(char *spaces, int *i, t_gnl *gnl)
{
	(*i)++;
	if (spaces[*i] >= '0' && spaces[*i] <= '9')
		while (spaces[*i] && spaces[*i] != SEPARATOR_CHAR)
		{
			if (spaces[*i] < '0' || spaces[*i] > '9')
				return (ft_syntax(NULL, 0, gnl, spaces[*i]));
			(*i)++;
		}
	if (spaces[*i] == LABEL_CHAR)
		if (!(ft_islab(spaces, i, gnl)))
			return (0);
	return (1);
}

static int		ft_aftersep(int *issep, char *spaces, int *i, t_gnl *gnl)
{
	while (spaces[*i] && spaces[*i] != SEPARATOR_CHAR)
	{
		if (spaces[*i] == DIRECT_CHAR)
		{
			if (!(ft_isdir(spaces, i, gnl)))
				return (0);
		}
		else if (spaces[*i] == LABEL_CHAR)
		{
			if (!(ft_islab(spaces, i, gnl)))
				return (0);
		}
		else if (spaces[*i] >= '0' && spaces[*i] <= '9')
		{
			while (spaces[*i] && spaces[*i] != SEPARATOR_CHAR)
			{
				if (spaces[*i] < '0' || spaces[*i] > '9')
					return (ft_syntax(NULL, 3, gnl, spaces[*i]));
				(*i)++;
			}
		}
		else if (spaces[*i] == 'r')
		{
			(*i)++;
			while (spaces[*i] && spaces[*i] != SEPARATOR_CHAR)
			{
				if (spaces[*i] < '0' || spaces[*i] > '9')
					return (ft_syntax(NULL, 3, gnl, spaces[*i]));
				(*i)++;
			}
		}
		(*i)++;
	}
	(*i)--;
	*issep = 0;
	return (1);
}

int				ft_separator(char **str, int nb, t_gnl *gnl)
{
	int		i;
	char	*spaces;
	int		issep;
	int		ret;

	issep = 0;
	ret = 1;
	if (!(spaces = ft_charwtspaces(*str)))
		ret = (ft_free(NULL, 2, gnl, str));
	i = -1;
	while (spaces[++i] && ret != 0)
	{
		if (spaces[i] == SEPARATOR_CHAR)
		{
			nb = (issep == 1) ? nb : nb - 1;
			ret = (issep == 1) ? ft_syntax(str, 0, gnl, spaces[i]) : ret;
			issep = 1;
		}
		else if (spaces[i] != SEPARATOR_CHAR)
			if (!(ft_aftersep(&issep, spaces, &i, gnl)))
			{
				ft_strdel(&spaces);
				return (0);
			}
		if (nb < 0 && ret > 0)
			ret = (ft_syntax(str, 1, gnl, 0));
	}
	ft_strdel(&spaces);
	return (nb != 0 && ret <= 0 ? ft_syntax(str, 1, gnl, 0) : ret);
}
