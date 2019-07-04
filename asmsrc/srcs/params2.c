/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 13:21:59 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/04 10:23:52 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/libft.h"

void	ft_paramldi(char **split, t_op *op)
{

	if (split[0])
		ft_fillinstop(split[0], op);
	if (!(ft_rgidd(split, op, (DIR_SIZE / 2) + 1, 1)))
		return ;
	if (!(ft_idd(split, op, (DIR_SIZE / 2) + 1, 2)))
		return ;
	if (split[3] && split[3][0] == 'r')
		ft_fillrg(split, 3, op);
	else
	{
		ft_printf("%s is not a register, did you mean %c%s ?\n", split[1],
					'r', split[1]);
			return ;
	}
	if (!split[1] || !split[2] || !split[3])
		ft_printf("Bad argument\n");
}

void	ft_paramsti(char **split, t_op *op)
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
}
