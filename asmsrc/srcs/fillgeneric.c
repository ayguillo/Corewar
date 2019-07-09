/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillgeneric.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:42:23 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/09 12:25:06 by ayguillo         ###   ########.fr       */
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

void		ft_filld(char **split, int nparam, t_op *op, int size)
{
	unsigned int	param;

	if (split[nparam] && split[nparam][0] == DIRECT_CHAR)
		param = ft_filllabel(op, split, nparam);
	if (nparam == 1)
		ft_fillparam1(op, size, DIR_CODE, param);
	if (nparam == 2)
		ft_fillparam2(op, size, DIR_CODE, param);
}

void		ft_filli(char **split, int nparam, t_op *op)
{
	unsigned int	param;
	int				i;

	i = -1;
	param = 0;
	if (split[nparam][0] == LABEL_CHAR)
	{
		param = ft_filllabel(op, split, nparam);
	}
	else
	{
		while (split[nparam][++i])
			if (split[nparam][i] < '0' || split[nparam][i] > '9')
			{
				ft_printf("%s is not indirect. Delete %c please.\n", split[nparam],
						split[nparam][i]);
				return ;
			}
	}
	if (split[nparam] && !param)
		param = ft_atui(split[nparam]);
	if (nparam == 1)
		ft_fillparam1(op, IND_SIZE + 1, IND_CODE, param);
	if (nparam == 2)
		ft_fillparam2(op, IND_SIZE + 1, IND_CODE, param);
}

void		ft_fillrg(char **split, int nparam, t_op *op)
{
	int		param;
	char	**reg;

	reg = NULL;
	if (!(reg = ft_strsplit(split[nparam], 'r')))
		return ;
	param = 0;
	if (reg[0])
	{
		if (((param = ft_atoi(reg[0])) <= 0) || param > REG_NUMBER)
		{
			ft_free_tab2d(&reg);
			ft_printf("Min register = 1 or Max register = %i\n", REG_NUMBER);
			return ;
		}
	}
	if (nparam == 1)
		ft_fillparam1(op, 2, REG_CODE, param);
	if (nparam == 2)
		ft_fillparam2(op, 2, REG_CODE, param);
	if (nparam == 3)
		ft_fillparam3(op, 2, REG_CODE, param);
	ft_free_tab2d(&reg);
}
