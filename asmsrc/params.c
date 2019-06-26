/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 12:14:08 by ayguillo          #+#    #+#             */
/*   Updated: 2019/06/25 16:07:52 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"
#include "../includes/asm.h"
#include "../libft/libft.h"

static void	ft_fillinstop(char *inst, t_op *op)
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
}

void		ft_paramd(char **split, t_op *op, int size)
{
	char			**dirsplit;
	t_op			*tmp;
	unsigned int	param;
	char			**label;

	tmp = op;
	if (split[0])
		ft_fillinstop(split[0], op);
	if (split[1] && split[1][0] != DIRECT_CHAR)
	{
		ft_printf("%s is not a direct, did you mean %c%s ?\n", split[1],
				DIRECT_CHAR, split[1]);
		return ;
	}
	if (split[1] && split[1][1] == LABEL_CHAR)
	{
		if (!(label = ft_strsplit(split[1], LABEL_CHAR)))
			return ;
		param = ft_paramlabel(tmp, label[1]);
	}
	else
	{
		if (!(dirsplit = ft_strsplit(split[1], DIRECT_CHAR)))
		{
			ft_free_tab2d(&label);
			return ;
		}
		param = ft_atui(dirsplit[0]);
	}
	ft_fillparam1(op, size, DIR_CODE, param);
	ft_free_tab2d(&label);
	ft_free_tab2d(&dirsplit);
}

void	ft_paramrg(char **split, t_op *op)
{
	t_op			*tmp;
	char			**reg;
	int				param;


	tmp = op;
	param = 0;
	if (split[0])
		ft_fillinstop(split[0], op);
	if (split[1] && split[1][0] != 'r')
	{
		ft_printf("%s is not a register, did you mean %c%s ?\n", split[1], 'r',
				split[1]);
		return ;
	}
	if (!(reg = ft_strsplit(split[1], 'r')))
		return;
	if (reg[0])
	{
		if ((param = ft_atoi(reg[0])) <= 0 || param > REG_NUMBER)
		{
			ft_printf("reg %i\n", param);
			ft_printf("Min register = 0 or Max registers = %i\n", REG_NUMBER);
			return ;
		}
	}
	ft_fillparam1(op, 1, REG_CODE, param);
	ft_free_tab2d(&reg);
}
