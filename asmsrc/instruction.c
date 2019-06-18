/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 14:06:21 by ayguillo          #+#    #+#             */
/*   Updated: 2019/06/18 16:55:55 by ayguillo         ###   ########.fr       */
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

int	ft_instok(char **line, char **trim)
{
	char	**split;
	int		nbarg;

	split = NULL;
	if (!(split = ft_splitandspaces(*trim, SEPARATOR_CHAR)))
		return (ft_free(&split, 2, line, NULL));
	if (!(nbarg = ft_isinst(split[0])))
		return (ft_freecom(&split, 3, split[0], line));
	if (!(ft_separator(trim, nbarg - 1, line)))
	{
		ft_free_tab2d(&split);
		return (0);
	}
	return (1);
}

int	ft_recupinst(char **line, char **trim, t_op *op)
{
	t_op	*tmp;
	t_op	*new;

	tmp = op;
	if (!(new = malloc(sizeof(t_op))))
	{
		ft_strdel(trim);
		return (0);
	}
	new->next = NULL;
	new->label = NULL;
	while (tmp)
		tmp = tmp->next;
	tmp = new;
	op = tmp;
	if (!(ft_label(*trim, line, op)))
	{
		ft_strdel(trim);
		return (0);
	}
	return (1);
}

int		ft_supprlab(char *trim, char **split)
{
	int		lensplit;
	int		len;
	int		i;

	if (!split[0])
		return (0);
	lensplit = ft_strlen(split[0]) + 1;
	len = ft_strlen(trim);
	i = 0;
	while (trim[lensplit])
	{
		trim[i] = trim[lensplit];
		lensplit++;
		i++;
	}
	trim[i] = '\0';
	return (1);
}

int		veriflabel(char *split)
{
	int		i;
	int		j;
	int		ok;

	i = -1;
	while (split[++i])
	{
		j = -1;
		ok = 0;
		while (LABEL_CHARS[++j])
			if (split[i] == LABEL_CHARS[j])
				ok = 1;
		if (ok == 0)
			return (0);
	}
	return (1);
}
