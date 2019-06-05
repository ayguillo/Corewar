/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:11:17 by ayguillo          #+#    #+#             */
/*   Updated: 2019/06/05 17:24:20 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/asm.h"

static int	ft_label(char *trim, char **line)
{
	char	**split;
	int		i;
	int		labchar;

	i = -1;
	labchar = 0;
	split = NULL;
	while (trim[++i])
		if (trim[i] == LABEL_CHAR)
			labchar++;
	if (labchar > 1)
		return (ft_freecom(NULL, 3, trim, line));
	else if (labchar == 1)
		if (!(split = ft_strsplit(trim, ':')))
			return (ft_free(&split, 2, line, NULL));
	//A CONTINUER
	ft_free_tab2d(&split);
	return (1);
}

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

static int	ft_recupinst(char **line, char **trim)
{
	char	**split;
	int		nbarg;

	split = NULL;
	if ((ft_label(*trim, line)) <= 0)
	{
		ft_strdel(trim);
		return (0);
	}
	if (!(split = ft_splitandspaces(*trim, SEPARATOR_CHAR)))
		return (ft_free(&split, 2, line, NULL));
	if (!(nbarg = ft_isinst(split[0])))
		return (ft_freecom(&split, 3, split[0], line));
	if (!(ft_separator(trim, nbarg - 1, line)))
			return (0);
	return (1);
}

int			ft_readinst(t_file file, int ret, char **line)
{
	char	*trim;
	int		i;

	trim = NULL;
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
			if ((ft_recupinst(line, &trim)) <= 0)
				return (0);
		}
		ft_strdel(line);
	}
	ft_strdel(&trim);
	return (1);
}
