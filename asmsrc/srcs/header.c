/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 10:26:46 by ayguillo          #+#    #+#             */
/*   Updated: 2019/06/19 15:03:53 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/asm.h"
#include <string.h>

static int	ft_com(char **trim, char **line, t_header *header, int *len)
{
	char	**com;

	com = NULL;
	if (!(com = ft_strsplit(*line, '\"')))
		return (ft_free(&com, 2, line, trim));
	if (!com[1])
		return (ft_free(&com, 0, line, trim));
	if ((*len = ft_strlen(com[1])) > COMMENT_LENGTH)
		return (ft_free(&com, 3, line, trim));
	if (!(ft_strcpy(header->comment, com[1])))
		return (ft_free(&com, 2, line, trim));
	ft_free_tab2d(&com);
	return (1);
}

int			ft_recupcom(t_header *header, char **line, int *len)
{
	char	**split;
	char	*trim;
	int		lensplit;
	int		i;

	lensplit = 0;
	if (!(trim = ft_strtrim(*line)))
		return (ft_free(NULL, 2, line, &trim));
	if (!(split = ft_splitwhitespaces(*line)))
		return (ft_free(&split, 2, line, &trim));
	if (ft_strcmp(split[0], COMMENT_CMD_STRING))
	{
		ft_strdel(&trim);
		return (ft_freecom(&split, 0, NULL, line));
	}
	if (!(split[1]))
		return (ft_free(&split, 0, line, &trim));
	while (split[lensplit])
		lensplit++;
	*len = ft_strlen(split[lensplit - 1]);
	if (split[1][0] != '\"' || split[lensplit - 1][*len - 1] != '\"')
	{
		ft_strdel(&trim);
		return (ft_freecom(&split, 1, "Comment", line));
	}
	i = ft_com(&trim, line, header, len);
	ft_free_tab2d(&split);
	return (i);
}

static int	ft_name(char **trim, t_header *header, int *len, char **line)
{
	char	**name;

	name = NULL;
	if (!(name = ft_strsplit(*trim, '\"')))
		return (ft_free(&name, 2, line, trim));
	if (!name[1])
		return (ft_free(&name, 0, line, trim));
	if ((*len = ft_strlen(name[1])) > PROG_NAME_LENGTH)
		return (ft_free(&name, 1, line, trim));
	if (!(ft_strcpy(header->prog_name, name[1])))
		return (ft_free(&name, 2, line, trim));
	ft_free_tab2d(&name);
	ft_strdel(trim);
	return (1);
}

int			ft_recupname(t_header *header, char **line, int *len)
{
	char	*trim;
	char	**split;
	int		lensplit;
	int		i;

	lensplit = 0;
	if (!(trim = ft_strtrim(*line)))
		return (ft_free(NULL, 2, line, &trim));
	if (!(split = ft_splitwhitespaces(*line)))
		return (ft_free(&split, 2, line, &trim));
	if (ft_strcmp(split[0], NAME_CMD_STRING))
	{
		ft_strdel(&trim);
		return (ft_freecom(&split, 0, NULL, line));
	}
	if (!(split[1]))
		return (ft_free(&split, 0, line, &trim));
	while (split[lensplit])
		lensplit++;
	*len = ft_strlen(split[lensplit - 1]);
	if (split[1][0] != '\"' || split[lensplit - 1][*len - 1] != '\"')
	{
		ft_strdel(&trim);
		return (ft_freecom(&split, 1, "Name", line));
	}
	i = ft_name(&trim, header, len, line);
	ft_free_tab2d(&split);
	return (i);
}
