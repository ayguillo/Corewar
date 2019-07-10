/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 13:21:59 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/10 11:01:39 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/libft.h"

int		ft_paramldi(char **split, t_op *op, t_gnl *gnl)
{
	if (split[0])
		ft_fillinstop(split[0], op);
	if (!(ft_rgidd(split, op, (DIR_SIZE / 2) + 1, 1, gnl)))
		return (0);
	if (!(ft_idd(split, op, (DIR_SIZE / 2) + 1, 2, gnl)))
		return (0);
	if (split[3] && split[3][0] == 'r')
	{
		if (!(ft_fillrg(split, 3, op, gnl)))
			return (0);
	}
	else
		return (ft_errorparams(gnl, 1, split[3][0], split[3]));
	return (1);
}

int		ft_paramsti(char **split, t_op *op, t_gnl *gnl)
{
	if (split[0])
		ft_fillinstop(split[0], op);
	if (split[1] && split[1][0] != 'r')
		return (ft_errorparams(gnl, 1, split[1][0], split[1]));
	ft_fillrg(split, 1, op, gnl);
	if (!(ft_rgidd(split, op, (DIR_SIZE / 2 + 1), 2, gnl)))
		return (0);
	if (!(ft_idd(split, op, (DIR_SIZE / 2) + 1, 3, gnl)))
		return (0);
	return (1);
}

int		ft_paramcomp(char **split, t_op *op, t_gnl *gnl)
{
	if (split[0])
		ft_fillinstop(split[0], op);
	if (!(ft_rgidd(split, op, DIR_SIZE + 1, 1, gnl)))
		return (0);
	if (!(ft_rgidd(split, op, DIR_SIZE + 1, 2, gnl)))
		return (0);
	if (split[3] && split[3][0] != 'r')
		return (ft_errorparams(gnl, 1, split[3][0], split[3]));
	ft_fillrg(split, 3, op, gnl);
	return (1);
}
