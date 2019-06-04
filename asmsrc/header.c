/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 10:26:46 by ayguillo          #+#    #+#             */
/*   Updated: 2019/05/30 14:40:06 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/asm.h"
#include <string.h>

static int	ft_com(char **line, t_header *header, int *len)
{
	char	**com;

	com = NULL;
	if (!(com = ft_strsplit(*line, '\"')))
		return (0);
	if (!com[1])
		return (ft_free(&com, 0, line));
	if ((*len = ft_strlen(com[1])) > COMMENT_LENGTH)
		return (ft_free(&com, 1, line));
	if (!(ft_strcpy(header->comment, com[1])))
		return (ft_free(&com, 2, line));
	ft_free_tab2d(&com);
	return (1);
}

int			ft_recupcom(t_header *header, char **line, int *len)
{
	char	**split;
	int		lensplit;
	int		i;

	lensplit = 0;
	if (!(split = ft_splitwhitespaces(*line)))
		return (0);
	if (ft_strcmp(split[0], COMMENT_CMD_STRING))
		return (ft_freecom(&split, 0, NULL, line));
	if (!(split[1]))
		return (ft_free(&split, 0, line));
	while (split[lensplit])
		lensplit++;
	*len = ft_strlen(split[lensplit - 1]);
	if (split[1][0] != '\"' || split[lensplit - 1][*len - 1] != '\"')
		return (ft_freecom(&split, 1, "Comment", line));
	i = ft_com(line, header, len);
	ft_free_tab2d(&split);
	return (i);
}

static int	ft_name(char **line, t_header *header, int *len)
{
	char	**name;

	name = NULL;
	if (!(name = ft_strsplit(*line, '\"')))
		return (0);
	if (!name[1])
		return (ft_free(&name, 0, line));
	if ((*len = ft_strlen(name[1])) > PROG_NAME_LENGTH)
		return (ft_free(&name, 1, line));
	if (!(ft_strcpy(header->prog_name, name[1])))
		return (ft_free(&name, 2, line));
	ft_free_tab2d(&name);
	return (1);
}

int			ft_recupname(t_header *header, char **line, int *len)
{
	char	**split;
	int		lensplit;
	int		i;

	lensplit = 0;
	if (!(split = ft_splitwhitespaces(*line)))
		return (0);
	if (ft_strcmp(split[0], NAME_CMD_STRING))
		return (ft_freecom(&split, 0, NULL, line));
	if (!(split[1]))
		return (ft_free(&split, 0, line));
	while (split[lensplit])
		lensplit++;
	*len = ft_strlen(split[lensplit - 1]);
	if (split[1][0] != '\"' || split[lensplit - 1][*len - 1] != '\"')
		return (ft_freecom(&split, 1, "Name", line));
	i = ft_name(line, header, len);
	ft_free_tab2d(&split);
	return (i);
}
