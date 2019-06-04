/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:11:17 by ayguillo          #+#    #+#             */
/*   Updated: 2019/06/04 16:53:21 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/asm.h"

short		ft_opc(int param1, int param2, int param3)
{
	short i;

	i = 0;
	i += param1;
	i = i << 2;
	i += param2;
	i = i << 2;
	i += param3;
	i = i << 2;
	return (i);
}

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
			return (ft_free(&split, 2, line));
	//A CONTINUER
	ft_free_tab2d(&split);
	return (1);
}

static int	ft_isinst(char *inst)
{
	if (ft_strcmp(inst, "live") && ft_strcmp(inst, "ld")
			&& ft_strcmp(inst, "st") && ft_strcmp(inst, "add")
			&& ft_strcmp(inst, "sub") && ft_strcmp(inst, "and")
			&& ft_strcmp(inst, "or") && ft_strcmp(inst, "xor")
			&& ft_strcmp(inst, "zjmp") && ft_strcmp(inst, "ldi")
			&& ft_strcmp(inst, "sti") && ft_strcmp(inst, "fork")
			&& ft_strcmp(inst, "lld") && ft_strcmp(inst, "lldi")
			&& ft_strcmp(inst, "lfork") && ft_strcmp(inst, "aff"))
		return (0);
	return (1);
}

static int	ft_recupinst(char **line, char *trim)
{
	char **split;

	split = NULL;
	if ((ft_label(trim, line)) <= 0)
		return (0);
	if (!(split = ft_splitandspaces(trim, SEPARATOR_CHAR)))
		return (ft_free(&split, 2, line));
	int i = -1;
	while (split[++i])
		ft_printf("split = %s\n", split[i]);
	if (!(ft_isinst(split[0])))
		return(ft_freecom(&split, 3, split[0], line));
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
		trim = ft_strtrim(*line);
		i = -1;
		while (trim[++i])
			if (trim[i] == COMMENT_CHAR)
			{
				trim[i] = '\0';
				break ;
			}
		if ((ft_recupinst(line, trim)) <= 0)
		{
			ft_strdel(&trim);
			return (0);
		}
		ft_strdel(line);
	}
	ft_strdel(&trim);
	return (1);
}
