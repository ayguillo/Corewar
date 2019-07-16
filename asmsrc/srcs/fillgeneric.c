/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillgeneric.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:42:23 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/16 15:54:11 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/libft.h"

void		ft_fillinstop2(char *inst, t_op *tmp)
{
	if (!(ft_strcmp(inst, "st")))
		tmp->inst = ST;
	else if (!(ft_strcmp(inst, "add")))
		tmp->inst = ADD;
	else if (!(ft_strcmp(inst, "sub")))
		tmp->inst = SUB;
	else if (!(ft_strcmp(inst, "lld")))
		tmp->inst = LLD;
	else if (!(ft_strcmp(inst, "lldi")))
		tmp->inst = LLDI;
	else if (!(ft_strcmp(inst, "sti")))
		tmp->inst = STI;
	else if (!(ft_strcmp(inst, "and")))
		tmp->inst = AND;
	else if (!(ft_strcmp(inst, "or")))
		tmp->inst = OR;
	else if (!(ft_strcmp(inst, "xor")))
		tmp->inst = XOR;
}

void		ft_fillinstop(char *inst, t_op *op)
{
	t_op	*tmp;

	tmp = op;
	while (tmp->next)
		tmp = tmp->next;
	if (!(ft_strcmp(inst, "live")))
		tmp->inst = LIVE;
	else if (!(ft_strcmp(inst, "zjmp")))
		tmp->inst = ZJMP;
	else if (!(ft_strcmp(inst, "ldi")))
		tmp->inst = LDI;
	else if (!(ft_strcmp(inst, "fork")))
		tmp->inst = FORK;
	else if (!(ft_strcmp(inst, "lfork")))
		tmp->inst = LFORK;
	else if (!(ft_strcmp(inst, "ld")))
		tmp->inst = LD;
	else if (!(ft_strcmp(inst, "lld")))
		tmp->inst = LLD;
	else
		ft_fillinstop2(inst, tmp);
}

int			ft_filld(char **split, t_asm *tasm, int size)
{
	unsigned int	param;

	tasm->error = 0;
	if (split[tasm->n_param] && split[tasm->n_param][0] == DIRECT_CHAR)
		param = ft_filllabel(tasm, split);
	if (tasm->error != 0)
	{
		return (0);
	}
	if (tasm->n_param == 1)
		ft_fillparam1(tasm->op, size, DIR_CODE, param);
	if (tasm->n_param == 2)
		ft_fillparam2(tasm->op, size, DIR_CODE, param);
	if (tasm->n_param == 3)
		ft_fillparam3(tasm->op, size, DIR_CODE, param);
	return (1);
}

int			ft_filli(char **split, t_asm *tasm)
{
	unsigned int	param;
	int				i;
	int				isop;

	i = 0;
	param = 0;
	isop = 0;
	if (split[tasm->n_param][0] == LABEL_CHAR)
		param = ft_filllabel(tasm, split);
	while (split[tasm->n_param][i] && split[tasm->n_param][i] != '\t' &&
			split[tasm->n_param][i] != ' ')
	{
		if (split[tasm->n_param][i] == '+' || split[tasm->n_param][i] == '-'
				|| (split[tasm->n_param][i] >= '0' && split[tasm->n_param][i] <= '9'))
			isop = 1;
		else if (((split[tasm->n_param][i] == '+' ||
				split[tasm->n_param][i] == '-') && isop == 1) ||
				split[tasm->n_param][i] < '0' || split[tasm->n_param][i] > '9')
		{
			tasm->error = 3;
			return (ft_syntax(NULL, tasm, split[tasm->n_param][i]));
		}
		i++;
	}
	if (split[tasm->n_param] && !param)
		param = ft_atui(split[tasm->n_param]);
	if (tasm->n_param == 1)
		ft_fillparam1(tasm->op, IND_SIZE, IND_CODE, param);
	if (tasm->n_param == 2)
		ft_fillparam2(tasm->op, IND_SIZE, IND_CODE, param);
	if (tasm->n_param == 3)
		ft_fillparam3(tasm->op, IND_SIZE, IND_CODE, param);
	return (1);
}

int			ft_fillrg(char **split, t_asm *tasm)
{
	int		param;
	char	**reg;
	int		i;

	reg = NULL;
	if (split[tasm->n_param][0] != 'r')
		return (ft_syntax(NULL, tasm, split[tasm->n_param][0]));
	if (!(reg = ft_strsplit(split[tasm->n_param], 'r')))
		return (ft_free(NULL, 2, &tasm->gnl, NULL));
	if (split[tasm->n_param][0] == 'r')
	{
		i = 0;
		while (split[tasm->n_param][++i])
		{
			if (split[tasm->n_param][i] < '0' || split[tasm->n_param][i] > '9')
			{
				tasm->error = 3;
				return (ft_syntax(NULL, tasm, split[tasm->n_param][i]));
			}
		}
	}
	param = 0;
	if (reg[0])
	{
		i = -1;
		if (((param = ft_atoi(reg[0])) <= 0) || param > REG_NUMBER)
		{
			ft_free_tab2d(&reg);
			tasm->error = 2;
			return (ft_errorparams(tasm, split[tasm->n_param]));
		}
	}
	else
	{
		tasm->error = 3;
		return (ft_syntax(NULL, tasm, split[0][0]));
	}
	if (tasm->n_param == 1)
		ft_fillparam1(tasm->op, 1, REG_CODE, param);
	if (tasm->n_param == 2)
		ft_fillparam2(tasm->op, 1, REG_CODE, param);
	if (tasm->n_param == 3)
		ft_fillparam3(tasm->op, 1, REG_CODE, param);
	ft_free_tab2d(&reg);
	return (1);
}
