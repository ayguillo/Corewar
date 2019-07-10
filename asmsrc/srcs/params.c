/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 12:14:08 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/10 12:41:04 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"
#include "../includes/asm.h"
#include "../libft/libft.h"

int			ft_paramd(char **split, t_op *op, int size, t_gnl *gnl)
{
	unsigned int	param;

	if (split[0])
		ft_fillinstop(split[0], op);
	if (split[1] && split[1][0] != DIRECT_CHAR)
		return (ft_errorparams(gnl, 0, split[1][0], split[1]));
	param = ft_filllabel(op, split, 1);
	ft_fillparam1(op, size, DIR_CODE, param);
	return (1);
}

int			ft_paramrg(char **split, t_op *op, t_gnl *gnl)
{
	char			**reg;
	int				param;

	param = 0;
	reg = NULL;
	if (split[0])
		ft_fillinstop(split[0], op);
	if (split[1] && split[1][0] != 'r')
		return (ft_errorparams(gnl, 1, split[1][0], split[1]));
	if (!(reg = ft_strsplit(split[1], 'r')))
		return (ft_free(NULL, 2, gnl, NULL));
	if (reg[0] && ((param = ft_atoi(reg[0])) <= 0 || param > REG_NUMBER))
	{
		ft_free_tab2d(&reg);
		return (ft_errorparams(gnl, 2, 0, split[1]));
	}
	ft_fillparam1(op, 2, REG_CODE, param);
	ft_free_tab2d(&reg);
	return (1);
}

int			ft_paramld(char **split, t_op *op, t_gnl *gnl)
{
	if (split[0])
		ft_fillinstop(split[0], op);
	if (!(ft_idd(split, op, DIR_SIZE + 1, 1, gnl)))
		return (0);
	if (split[2])
	{
		if (split[2][0] != 'r')
			return (ft_errorparams(gnl, 1, split[2][0], split[2]));
		if (!(ft_fillrg(split, 2, op, gnl)))
			return (0);
	}
	return (1);
}

int			ft_paramst(char **split, t_op *op, t_gnl *gnl)
{
	if (split[0])
		ft_fillinstop(split[0], op);
	if (split[1])
	{
		if (split[1] && split[1][0] != 'r')
			return (ft_errorparams(gnl, 1, split[1][0], split[1]));
		if (!(ft_fillrg(split, 1, op, gnl)))
			return (0);
	}
	if (!(ft_rgid(split, op, 2, gnl)))
		return (0);
	return (1);
}

int			ft_param3rg(char **split, t_op *op, t_gnl *gnl)
{
	int		i;

	i = 0;
	if (split[0])
		ft_fillinstop(split[0], op);
	while (++i <= 3 && split[i])
	{
		if (split[i][0] != 'r')
			return (ft_errorparams(gnl, 1, split[i][0], split[i]));
		if (!(ft_fillrg(split, i, op, gnl)))
			return (0);
	}
	return (1);
}
