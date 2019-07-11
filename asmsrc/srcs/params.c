/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 12:14:08 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/11 13:43:08 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"
#include "../includes/asm.h"
#include "../libft/libft.h"

int			ft_paramd(char **split, t_asm *tasm, int size)
{
	unsigned int	param;

	tasm->n_param = 1;
	if (split[0])
		ft_fillinstop(split[0], tasm->op);
	if (split[1] && split[1][0] != DIRECT_CHAR)
	{
		tasm->error = 0;
		return (ft_errorparams(tasm, split[1]));
	}
	param = ft_filllabel(tasm, split);
	ft_fillparam1(tasm->op, size, DIR_CODE, param);
	return (1);
}

int			ft_paramrg(char **split, t_asm *tasm)
{
	char			**reg;
	int				param;

	param = 0;
	reg = NULL;
	tasm->n_param = 1;
	if (split[0])
		ft_fillinstop(split[0], tasm->op);
	if (split[1] && split[1][0] != 'r')
	{
		tasm->error = 1;
		return (ft_errorparams(tasm, split[1]));
	}
	if (!(reg = ft_strsplit(split[1], 'r')))
		return (ft_free(NULL, 2, &(tasm->gnl), NULL));
	if (reg[0] && ((param = ft_atoi(reg[0])) <= 0 || param > REG_NUMBER))
	{
		ft_free_tab2d(&reg);
		tasm->error = 2;
		return (ft_errorparams(tasm, split[1]));
	}
	ft_fillparam1(tasm->op, 2, REG_CODE, param);
	ft_free_tab2d(&reg);
	return (1);
}

int			ft_paramld(char **split, t_asm *tasm)
{
	if (split[0])
		ft_fillinstop(split[0], tasm->op);
	tasm->n_param = 1;
	if (!(ft_idd(split, tasm, DIR_SIZE + 1)))
		return (0);
	if (split[2])
	{
		tasm->n_param = 2;
		if (split[2][0] != 'r')
		{
			tasm->error = 1;
			return (ft_errorparams(tasm, split[1]));
		}
		if (!(ft_fillrg(split, tasm)))
			return (0);
	}
	return (1);
}

int			ft_paramst(char **split, t_asm *tasm)
{
	if (split[0])
		ft_fillinstop(split[0], tasm->op);
	if (split[1])
	{
		tasm->n_param = 1;
		if (split[1] && split[1][0] != 'r')
		{
			tasm->error = 1;
			return (ft_errorparams(tasm, split[1]));
		}
		if (!(ft_fillrg(split, tasm)))
			return (0);
	}
	if (!(ft_rgid(split, tasm)))
		return (0);
	return (1);
}

int			ft_param3rg(char **split, t_asm *tasm)
{
	int		i;

	i = 0;
	if (split[0])
		ft_fillinstop(split[0], tasm->op);
	while (++i <= 3 && split[i])
	{
		tasm->n_param = i;
		if (split[i][0] != 'r')
		{
			tasm->error = 1;
			return (ft_errorparams(tasm, split[1]));
		}
		if (!(ft_fillrg(split, tasm)))
			return (0);
	}
	return (1);
}
