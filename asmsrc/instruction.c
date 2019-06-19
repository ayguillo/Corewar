/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 14:06:21 by ayguillo          #+#    #+#             */
/*   Updated: 2019/06/19 15:48:08 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdlib.h>
#include "../includes/asm.h"

static int	ft_isinst(char *inst)
{
	if (!ft_strcmp(inst, "live") || !ft_strcmp(inst, "zjmp")
				|| !ft_strcmp(inst, "fork") || !ft_strcmp(inst, "lfork")
				|| !ft_strcmp(inst, "aff"))
		return (1);
	else if (!ft_strcmp(inst, "ld") || !ft_strcmp(inst, "st")
				|| !ft_strcmp(inst, "lld"))
		return (2);
	else if (!ft_strcmp(inst, "add") || !ft_strcmp(inst, "sub")
				|| !ft_strcmp(inst, "and") || !ft_strcmp(inst, "or")
				|| !ft_strcmp(inst, "xor") || !ft_strcmp(inst, "ldi")
				|| !ft_strcmp(inst, "sti") || !ft_strcmp(inst, "lldi"))
		return (3);
	return (0);
}

static char	**ft_instok(char **line, char **trim)
{
	char	**split;
	int		nbarg;

	split = NULL;
	if (!(split = ft_splitandspaces(*trim, SEPARATOR_CHAR)))
	{
		ft_free(&split, 2, line, NULL);
		return (NULL);
	}
	if (!(nbarg = ft_isinst(split[0])))
	{
		ft_freecom(&split, 3, split[0], line);
		return (NULL);
	}
	if (!(ft_separator(trim, nbarg - 1, line)))
	{
		ft_free_tab2d(&split);
		return (NULL);
	}
	return (split);
}

int			ft_instructions(char **trim, char **line, t_op **op)
{
	char	*strim;
	char	**split;

	if (!(strim = ft_strtrim(*trim)))
		return (ft_free(NULL, 2, line, trim));
	ft_strdel(trim);
	if (!(split = ft_instok(line, &strim)))
	{
		ft_strdel(line);
		ft_strdel(&strim);
		return (0);
	}
	int	i;

	i = -1;
	while (*op && split[++i])
	{
		ft_printf("split = %s && label = %s\n", split[i], (*op)->label);
		(*op) = (*op)->next;
	}
	return (1);
}
