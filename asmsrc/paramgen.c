/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paramgen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:44:33 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/02 17:10:49 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/libft.h"

int		ft_idd(char **split, t_op *op, int size, int nparam)
{
	if (split[nparam])
	{
		if (split[nparam][0] == DIRECT_CHAR)
			ft_filld(split, nparam, op, size);
		else if (split[nparam][0] >= '0' && split[nparam][0] <= '9')
			ft_filli(split, nparam, op);
		else
		{
			ft_printf("Syntax %s invalid.", split[nparam]);
			return (0);
		}
	}
	else
	{
		ft_printf("Bad argument");
		return (0);
	}
	return (1);
}

int		ft_rgidd(char **split, t_op *op, int size, int nparam)
{
	if (split[nparam])
	{
		if (split[nparam][0] == 'r')
			ft_fillrg(split, nparam, op);
		else if (split[nparam][0] == DIRECT_CHAR)
			ft_filld(split, nparam, op, size);
		else
			ft_filli(split, nparam, op);
	}
	else
	{
		ft_printf("Syntax %s invalid", split[nparam]);
		return (0);
	}
	return (1);
}

int		ft_rgid(char **split, t_op *op, int nparam)
{
	if (split[nparam])
	{
		if (split[nparam][0] == 'r')
			ft_fillrg(split, nparam, op);
		else if (split[nparam][0] >= '0' && split[nparam][0] <= '9')
			ft_filli(split, nparam, op);
		else
		{
			ft_printf("Syntax %s invalid", split[nparam]);
			return (0);
		}
	}
	else
	{
		ft_printf("Bad argument");
		return (0);
	}
	return (1);
}
