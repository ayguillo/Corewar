/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:11:17 by ayguillo          #+#    #+#             */
/*   Updated: 2019/06/24 12:32:56 by ayguillo         ###   ########.fr       */
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
	if (!ft_strcmp(spaces[0], "live") || !ft_strcmp(spaces[0], "zjmp")
			|| !ft_strcmp(spaces[0], "fork") || !ft_strcmp(spaces[0], "lfork")
			|| !ft_strcmp(spaces[0], "aff") || !ft_strcmp(spaces[0], "ld")
			|| !ft_strcmp(spaces[0], "st") || !ft_strcmp(spaces[0], "lld")
			||	!ft_strcmp(spaces[0], "add") || !ft_strcmp(spaces[0], "sub")
			|| !ft_strcmp(spaces[0], "and") || !ft_strcmp(spaces[0], "or")
			|| !ft_strcmp(spaces[0], "xor") || !ft_strcmp(spaces[0], "ldi")
			|| !ft_strcmp(spaces[0], "sti") || !ft_strcmp(spaces[0], "lldi"))
	{
		ft_free_tab2d(&spaces);
		return (2);
	}
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

int			ft_label(char *trim, char **line, t_op *new)
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
		ret = ft_freecom(NULL, 3, trim, line);
	else if (labchar == 1)
	{
		if (!(split = ft_strsplit(trim, ':')))
			ret = ft_free(&split, 2, line, NULL);
		if (ret > 0)
		{
			if (!(verif = veriflabel(split[0])))
				ret = ft_freecom(&split, 3, split[0], line);
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

static int	ft_recupinst(char **line, char **trim, t_op **op)
{
	t_op	*tmp;
	t_op	*new;

	tmp = *op;
	if (!(new = ft_memalloc(sizeof(t_op))))
		return (ft_free(NULL, 2, line, trim));
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*op = new;
	if (!(ft_label(*trim, line, new)))
	{
		ft_strdel(trim);
		return (0);
	}
	if (!(ft_instructions(trim, line, op)))
		return (0);
	return (1);
}

int			ft_readinst(t_file file, int ret, char **line)
{
	char	*trim;
	int		i;
	t_op	*op;

	trim = NULL;
	op = NULL;
	while ((ret = ft_gnl(file.fdopen, line)) > 0)
	{
		ft_strdel(&trim);
		if (*line)
		{
			if (!(trim = ft_strtrim(*line)))
				return (ft_free(NULL, 2, line, NULL));
			i = -1;
			while (trim[++i])
				if (trim[i] == COMMENT_CHAR)
					trim[i] = '\0';
			if ((ft_recupinst(line, &trim, &op)) <= 0)
			{
				ft_strdel(&trim);
				ft_strdel(line);
				return (0);
			}
		}
		ft_strdel(line);
	}
	ft_strdel(&trim);
	return (1);
}
