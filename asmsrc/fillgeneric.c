/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillgeneric.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:42:23 by ayguillo          #+#    #+#             */
/*   Updated: 2019/06/26 15:19:14 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/libft.h"

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
	else if (!(ft_strcmp(inst, "fork")))
		tmp->inst = FORK;
	else if (!(ft_strcmp(inst, "lfork")))
		tmp->inst = LFORK;
	else if (!(ft_strcmp(inst, "ld")))
		tmp->inst = LD;
	else if (!(ft_strcmp(inst, "lld")))
		tmp->inst = LLD;
}

void		ft_filld(char **split, int nparam, t_op *op, int size)
{
	unsigned int	param;

	if (split[0] && !(op->inst))
		ft_fillinstop(split[0], op);
	if (split[nparam] && split[nparam][0] == DIRECT_CHAR)
		param = ft_filllabel(op, split);
	if (nparam == 1)
		ft_fillparam1(op, size, DIR_CODE, param);
}

void		ft_filli(char **split, int nparam, t_op *op)
{
	unsigned int	param;

	if (split[0] && !(op->inst))
		ft_fillinstop(split[0], op);
	if (split[nparam])
		param = ft_atui(split[nparam]);
	if (nparam == 1)
		ft_fillparam1(op, IND_SIZE, IND_CODE, param);
}

void		ft_fillrg(char **split, int nparam, t_op *op)
{
	int		param;
	char	**reg;

	if (!(reg = ft_strsplit(split[nparam], 'r')))
		return ;
	if (reg[0])
	{
		if ((param = ft_atoi(reg[0]) <= 0) || param > REG_NUMBER)
		{
			ft_strdel(reg);
			ft_printf("Min register = 1 or Max register = %i\n", REG_NUMBER);
			return ;
		}
	}
	if (nparam == 2)
		ft_fillparam2(op, 1, REG_CODE, param);
	ft_strdel(reg);
}
