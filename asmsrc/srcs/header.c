/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 10:26:46 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/05 13:22:15 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/asm.h"
#include <string.h>

static void		ft_supprcomment(char **trim)
{
	int		i;

	i = -1;
	while ((*trim)[++i])
	{
		if ((*trim)[i] == COMMENT_CHAR)
			(*trim)[i] = '\0';
	}
}

static int	ft_com(char **trim, t_gnl *gnl, t_header *header, int *len)
{
	char	**com;

	com = NULL;
	if (!(com = ft_strsplit(gnl->line, '\"')))
		return (ft_free(&com, 2, gnl, trim));
	if (!com[1])
		return (ft_free(&com, 0, gnl, trim));
	if ((*len = ft_strlen(com[1])) > COMMENT_LENGTH)
		return (ft_free(&com, 3, gnl, trim));
	if (!(ft_strcpy(header->comment, com[1])))
		return (ft_free(&com, 2, gnl, trim));
	ft_free_tab2d(&com);
	return (1);
}

int			ft_recupcom(t_header *header, t_gnl *gnl, int *len)
{
	char	**split;
	char	*trim;
	int		lensplit;
	int		i;

	lensplit = 0;
	if (!(trim = ft_strtrim(gnl->line)))
		return (ft_free(NULL, 2, gnl, &trim));
	ft_supprcomment(&trim);
	if (!(split = ft_splitwhitespaces(trim)))
		return (ft_free(&split, 2, gnl, &trim));
	if (ft_strcmp(split[0], COMMENT_CMD_STRING))
	{
		ft_strdel(&trim);
		return (ft_freecom(&split, 0, COMMENT_CMD_STRING, gnl));
	}
	if (!(split[1]))
		return (ft_free(&split, 0, gnl, &trim));
	while (split[lensplit])
		lensplit++;
	*len = ft_strlen(split[lensplit - 1]);
	if (split[1][0] != '\"' || split[lensplit - 1][*len - 1] != '\"')
	{
		ft_strdel(&trim);
		return (ft_freecom(&split, 1, "Comment", gnl));
	}
	i = ft_com(&trim, gnl, header, len);
	ft_free_tab2d(&split);
	return (i);
}

static int	ft_name(char **trim, t_header *header, int *len, t_gnl *gnl)
{
	char	**name;

	name = NULL;
	if (!(name = ft_strsplit(*trim, '\"')))
		return (ft_free(&name, 2, gnl, trim));
	if (!name[1])
	{
		ft_dprintf(2, "debug 4 %s\n", gnl->line);
		return (ft_free(&name, 0, gnl, trim));
	}
	if ((*len = ft_strlen(name[1])) > PROG_NAME_LENGTH)
		return (ft_free(&name, 1, gnl, trim));
	if (!(ft_strcpy(header->prog_name, name[1])))
		return (ft_free(&name, 2, gnl, trim));
	ft_free_tab2d(&name);
	ft_strdel(trim);
	return (1);
}

int			ft_recupname(t_header *header, t_gnl *gnl, int *len)
{
	char	*trim;
	char	**split;
	int		lensplit;
	int		i;
	int		ret;

	lensplit = 0;
	if (!(trim = ft_strtrim(gnl->line)))
		return (ft_free(NULL, 2, gnl, &trim));
	ft_supprcomment(&trim);
	if (!(split = ft_splitwhitespaces(trim)))
		return (ft_free(&split, 2, gnl, &trim));
	if (ft_strcmp(split[0], NAME_CMD_STRING))
	{
		ft_strdel(&trim);
		return (ft_freecom(&split, 0, NAME_CMD_STRING, gnl));
	}
	if (!(split[1]))
		return (ft_free(&split, 0, gnl, &trim));
	while (split[lensplit])
		lensplit++;
	*len = ft_strlen(split[lensplit - 1]);
	if (split[1][0] != '\"' || split[lensplit - 1][*len - 1] != '\"')
	{
		ft_strdel(&trim);
		return (ft_freecom(&split, 1, "Name", gnl));
	}
	i = ft_name(&trim, header, len, gnl);
	ft_free_tab2d(&split);
	return (i);
}
