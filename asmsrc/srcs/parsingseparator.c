/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingseparator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 12:04:50 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/12 15:54:59 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../includes/op.h"
#include "../libft/libft.h"
#include <stdlib.h>

static int		ft_islab(char *spaces, int *i, t_asm *tasm)
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
		{
			tasm->error = 3;
			tasm->n_param = 1;
			return (ft_syntax(NULL, tasm, spaces[*i]));
		}
		(*i)++;
	}
	return (1);
}

static int		ft_isdir(char *spaces, int *i, t_asm *tasm)
{
	int		isop;


	(*i)++;
	isop = 0;
	if (spaces[*i] == '\0')
		return (0);
	if ((spaces[*i] >= '0' && spaces[*i] <= '9') || spaces[*i] == '+' ||
			spaces[*i] == '-')
	{
		while (spaces[*i] && spaces[*i] != SEPARATOR_CHAR)
		{
			if (spaces[*i] == '+' || spaces[*i] == '-'
					|| (spaces[*i] >= 0 && spaces[*i] <= 9 && isop == 0))
				isop = 1;
			else if (((spaces[*i] == '+' || spaces[*i] == '-') && isop == 1) ||
					spaces[*i] < '0' || spaces[*i] > '9')
			{
				tasm->error = 0;
				tasm->n_param = 1;
				return (ft_syntax(NULL, tasm, spaces[*i]));
			}
			(*i)++;
		}
	}
	if (spaces[*i] == LABEL_CHAR)
		if (!(ft_islab(spaces, i, tasm)))
			return (0);
	(*i)--;
	return (1);
}

static int		ft_aftersep(int *issep, char *spaces, int *i, t_asm *tasm)
{
	int		j;

	j = 0;
	while (spaces[*i] && spaces[*i] != SEPARATOR_CHAR)
	{
		if (spaces[*i] == DIRECT_CHAR)
		{
			if (!(ft_isdir(spaces, i, tasm)))
				return (0);
		}
		else if (spaces[*i] == LABEL_CHAR)
		{
			if (!(ft_islab(spaces, i, tasm)))
				return (0);
		}
		else if (spaces[*i] >= '0' && spaces[*i] <= '9')
		{
			while (spaces[*i] && spaces[*i] != SEPARATOR_CHAR)
			{
				if (spaces[*i] < '0' || spaces[*i] > '9')
				{
					tasm->error = 3;
					return (ft_syntax(NULL, tasm, spaces[*i]));
				}
				(*i)++;
				j = 1;
			}
		}
		if (j == 0)
			(*i)++;
		j = 0;
	}
	(*i)--;
	*issep = 0;
	return (1);
}

int				ft_separator(char **str, int nb, t_asm *tasm)
{
	int		i;
	char	*spaces;
	int		issep;
	int		ret;

	issep = 0;
	ret = 1;
	tasm->n_param = 1;
	if (!(spaces = ft_charwtspaces(*str)))
		ret = (ft_free(NULL, 2, &(tasm->gnl), str));
	i = -1;
	while (spaces[++i] && ret != 0)
	{
		if (spaces[i] == SEPARATOR_CHAR)
		{
			tasm->n_param++;
			tasm->error = 0;
			nb = (issep == 1) ? nb : nb - 1;
			ret = (issep == 1) ? ft_syntax(str, tasm, spaces[i]) : ret;
			issep = 1;
		}
		else if (spaces[i] != SEPARATOR_CHAR)
		{
			if (!(ft_aftersep(&issep, spaces, &i, tasm)))
			{
				ft_strdel(&spaces);
				return (0);
			}
		}
		if (nb < 0 && ret > 0)
		{
			tasm->error = 0;
			tasm->n_param = 1;
			ret = (ft_syntax(str, tasm, 0));
		}
	}
	ft_strdel(&spaces);
	tasm->error = 1;
	tasm->n_param = 1;
	return (nb != 0 && ret <= 0 ? ft_syntax(str, tasm, 0) : ret);
}
