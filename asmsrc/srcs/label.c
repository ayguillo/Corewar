/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:11:17 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/16 15:50:04 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/asm.h"
#include <stdlib.h>

static void	ft_supprlab(char *trim, char **split)
{
	int		lensplit;
	int		len;
	int		i;

	if (!split[0])
		return ;
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
}

static int	veriflabel(char *split)
{
	int		i;
	int		j;
	int		ok;
	char	**spaces;

	i = -1;
	if (!(spaces = ft_splitwhitespaces(split)))
		return (0);
	ft_free_tab2d(&spaces);
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

static int		ft_label(char *trim, t_gnl *gnl, t_op *new)
{
	char	**split;
	int		i;
	int		labchar;
	int		ret;
	int		verif;

	i = -1;
	labchar = 0;
	split = NULL;
	ret = 1;
	while (trim[++i] && ((trim[i] < 9 || trim[i] > 13) && trim[i] != 32))
		if (trim[i] == LABEL_CHAR)
			labchar++;
	if (labchar == 0)
		ret = -1;
	else if (labchar > 1)
		ret = ft_freecom(NULL, 3, trim, gnl);
	else if (labchar == 1)
	{
		if (!(split = ft_strsplit(trim, ':')))
			ret = ft_free(&split, 2, gnl, NULL);
		if (ret > 0)
		{
			if (!(verif = veriflabel(split[0])))
				ret = ft_freecom(&split, 3, split[0], gnl);
			if (split[0] && verif != 2)
			{
				ft_supprlab(trim, split);
				new->label = ft_strdup(split[0]);
			}
		}
	}
	ft_free_tab2d(&split);
	return (ret);
}

static int	ft_recupinst(t_asm *tasm, char **trim)
{
	t_op	*tmp;
	t_op	*new;

	tmp = tasm->op;
	if (!(*trim[0]))
	{
		ft_strdel(trim);
		return (1);
	}
	if (!(new = ft_memalloc(sizeof(t_op))))
		return (ft_free(NULL, 2, &(tasm->gnl), trim));
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		tasm->op = new;
	if (!(ft_label(*trim, &(tasm->gnl), new)))
	{
		ft_strdel(trim);
		return (0);
	}
	ft_fillparam1(tasm->op, 0, 0, 0);
	if (!(ft_instructions(trim, tasm)))
		return (0);
	return (1);
}

int			ft_readinst(t_asm *tasm)
{
	char	*trim;
	int		i;

	trim = NULL;
	while ((ft_retgnl(tasm, 0)) > 0)
	{
		ft_strdel(&trim);
		if (tasm->gnl.line)
		{
			if (!(trim = ft_strtrim(tasm->gnl.line)))
				return (ft_free(NULL, 2, &(tasm->gnl), NULL));
			i = -1;
			while (trim[++i])
				if (trim[i] == COMMENT_CHAR)
					trim[i] = '\0';
			if ((ft_recupinst(tasm, &trim)) <= 0)
			{
				ft_strdel(&trim);
				ft_strdel(&(tasm->gnl.line));
				return (0);
			}
		}
		ft_strdel(&(tasm->gnl.line));
	}
	ft_strdel(&trim);
	return (1);
}
