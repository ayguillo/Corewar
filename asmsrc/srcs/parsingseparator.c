/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingseparator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 12:04:50 by ayguillo          #+#    #+#             */
/*   Updated: 2019/08/06 15:10:31 by vlambert         ###   ########.fr       */
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
				break ;
		if (LABEL_CHARS[j] == '\0')
		{
			tasm->error = 3;
			tasm->n_param = 1;
			return (ft_syntax(NULL, tasm, spaces[*i]));
		}
		(*i)++;
	}
	(*i)--;
	return (1);
}

static int		ft_isdir(char *spaces, int *i, t_asm *tasm)
{
	int		isop;

	isop = 0;
	if (spaces[++(*i)] == '\0')
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

static int		ft_check_separ(char **str, char **spaces, t_asm *tasm,
					int counters[4])
{
	if ((*spaces)[counters[3]] == SEPARATOR_CHAR)
	{
		tasm->n_param++;
		tasm->error = 0;
		counters[NB] = (counters[ISSEP] == 1) ? counters[NB] : counters[NB] - 1;
		counters[RET] = (counters[ISSEP] == 1) ?
			ft_syntax(str, tasm, (*spaces)[counters[I]]) : counters[RET];
		counters[ISSEP] = 1;
	}
	else if ((*spaces)[counters[I]] != SEPARATOR_CHAR)
	{
		if (!(ft_aftersep(counters, *spaces, counters + I, tasm)))
		{
			ft_strdel(spaces);
			return (0);
		}
	}
	if (counters[NB] < 0 && counters[RET] > 0)
	{
		tasm->error = 1;
		tasm->n_param = 1;
		counters[RET] = (ft_syntax(str, tasm, 0));
	}
	return (1);
}

int				ft_separator(char **str, int nb, t_asm *tasm)
{
	int		counters[4];
	char	*spaces;

	counters[ISSEP] = 0; //issep
	counters[RET] = 1; //ret
	counters[NB] = nb; //nb
	spaces = NULL;
	if (!(spaces = ft_charwtspaces(*str)))
		return (ft_free(NULL, 2, &(tasm->gnl), str));
	counters[I] = -1; //i
	while (spaces && spaces[++(counters[I])] && counters[RET] != 0)
	{
		if (!(ft_check_separ(str, &spaces, tasm, counters)))
			return (0);
	}
	ft_strdel(&spaces);
	tasm->error = 1;
	tasm->n_param = 1;
	if (counters[NB] != 0 && counters[RET] > 0)
		counters[RET] = ft_syntax(str, tasm, 0);
	return (counters[RET]);
}
