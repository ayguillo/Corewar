/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paramgen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:44:33 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/10 10:58:40 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/libft.h"

int		ft_idd(char **split, t_op *op, int size, int nparam, t_gnl *gnl)
{
	if (split[nparam])
	{
		if (split[nparam][0] == DIRECT_CHAR)
			ft_filld(split, nparam, op, size);
		else if (split[nparam][0] == LABEL_CHAR ||
				(split[nparam][0] >= '0' && split[nparam][0] <= '9'))
		{
			if (!(ft_filli(split, nparam, op, gnl)))
				return (0);
		}
		else
		{
			ft_printf("Syntax %s invalid.\n", split[nparam]);
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

int		ft_rgidd(char **split, t_op *op, int size, int nparam, t_gnl *gnl)
{
	if (split[nparam])
	{
		if (split[nparam][0] == 'r')
		{
			if (!(ft_fillrg(split, nparam, op, gnl)))
				return (0);
		}
		else if (split[nparam][0] == DIRECT_CHAR)
			ft_filld(split, nparam, op, size);
		else
		{
			if (!(ft_filli(split, nparam, op, gnl)))
				return (0);
		}
	}
	else
	{
		ft_printf("Syntax %s invalid", split[nparam]);
		return (0);
	}
	return (1);
}

int		ft_rgid(char **split, t_op *op, int nparam, t_gnl *gnl)
{
	if (split[nparam])
	{
		if (split[nparam][0] == 'r')
		{
			if (!(ft_fillrg(split, nparam, op, gnl)))
				return (0);
		}
		else if (split[nparam][0] >= '0' && split[nparam][0] <= '9')
		{
			if (!(ft_filli(split, nparam, op, gnl)))
				return (0);
		}
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
