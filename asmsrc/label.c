/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:11:17 by ayguillo          #+#    #+#             */
/*   Updated: 2019/06/18 17:14:31 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/asm.h"
#include <stdlib.h>


int	ft_label(char *trim, char **line, t_op **op)
{
	char	**split;
	int		i;
	int		labchar;
	int		ret;
	t_op	*tmp;

	i = -1;
	labchar = 0;
	split = NULL;
	ret = 1;
	while (trim[++i] && trim[i] != ' ')
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
			tmp = *op;
			while (tmp->next)
				tmp = tmp->next;
			if (split[0])
				tmp->label = ft_strdup(split[0]);
			if (!(veriflabel(split[0])))
				ret = ft_freecom(&split, 3, NULL, line);
			ft_supprlab(trim, split);
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
	if (!(new = malloc(sizeof(t_op))))
	{
		ft_strdel(trim);
		return (0);
	}
	new->next = NULL;
	new->label = NULL;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*op = new;
	if (!(ft_label(*trim, line, op)))
	{
		ft_strdel(trim);
		return (0);
	}
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
				ft_strdel(line);
				return (0);
			}
		}
		ft_strdel(line);
	}
	ft_strdel(&trim);
	return (1);
}
