/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paramgen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:44:33 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/11 12:39:11 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/libft.h"

int		ft_idd(char **split, t_asm *tasm, int size)
{
	if (split[tasm->n_param])
	{
		if (split[tasm->n_param][0] == DIRECT_CHAR)
			ft_filld(split, tasm, size);
		else if (split[tasm->n_param][0] == LABEL_CHAR ||
				(split[tasm->n_param][0] >= '0' && split[tasm->n_param][0] <= '9'))
		{
			if (!(ft_filli(split, tasm)))
				return (0);
		}
		else
		{
			tasm->error = 0;
			return (ft_errorparams(tasm, split[tasm->n_param]));
		}
	}
	else
	{
		ft_printf("Bad argument");
		return (0);
	}
	return (1);
}

int		ft_rgidd(char **split, t_asm *tasm, int size)
{
	if (split[tasm->n_param])
	{
		if (split[tasm->n_param][0] == 'r')
		{
			if (!(ft_fillrg(split, tasm)))
				return (0);
		}
		else if (split[tasm->n_param][0] == DIRECT_CHAR)
			ft_filld(split, tasm, size);
		else
		{
			if (!(ft_filli(split, tasm)))
				return (0);
		}
	}
	else
	{
		ft_printf("Syntax %s invalid\n", split[tasm->n_param]);
		return (0);
	}
	return (1);
}

int		ft_rgid(char **split, t_asm *tasm)
{
	if (split[tasm->n_param])
	{
		if (split[tasm->n_param][0] == 'r')
		{
			if (!(ft_fillrg(split, tasm)))
				return (0);
		}
		else if (split[tasm->n_param][0] >= '0' && split[tasm->n_param][0] <= '9')
		{
			if (!(ft_filli(split, tasm)))
				return (0);
		}
		else
		{
			ft_printf("Syntax %s invalid\n", split[tasm->n_param]);
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
