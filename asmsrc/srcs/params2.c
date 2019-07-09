/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 13:21:59 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/09 16:58:15 by ayguillo         ###   ########.fr       */
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
	if (!(ft_idd(split, op, (DIR_SIZE / 2) + 1, 2)))
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

/*void	ft_paramsti(char **split, t_op *op)
{
	if (split[0])
		ft_fillinstop(split[0], op);
	if (split[1] && split[1][0] != 'r')
	{
		ft_printf("%s is not a register, did you mean %c%s ?\n", split[1],
				'r', split[1]);
		return ;
	}
	ft_fillrg(split, 1, op);
	if (!(ft_rgidd(split, op, (DIR_SIZE / 2 + 1), 2)))
		return ;
	if (!(ft_idd(split, op, (DIR_SIZE / 2) + 1, 3)))
		return ;
	if (!split[1] || !split[2] || !split[3])
		ft_printf("Bad argument\n");
}

void	ft_paramcomp(char **split, t_op *op)
{
	if (split[0])
		ft_fillinstop(split[0], op);
	if (!(ft_rgidd(split, op, DIR_SIZE + 1, 1)))
		return ;
	if (!(ft_rgidd(split, op, DIR_SIZE + 1, 2)))
		return ;
	if (split[3] && split[1][0] != 'r')
	{
		ft_printf("%s is not a register, did you mean %c%s ?\n", split[3],
				'r', split[3]);
		return ;
	}
	ft_fillrg(split, 3, op);
}*/
