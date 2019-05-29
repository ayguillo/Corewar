/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 10:26:46 by ayguillo          #+#    #+#             */
/*   Updated: 2019/05/29 13:52:12 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/asm.h"
#include <string.h>

static int	ft_com(char *line, t_header *header, t_file file)
{
	char	**com;
	int		len;

	com = NULL;
	if (!(com = ft_strsplit(line, '\"')))
		return (0);
	if (!com[1])
		return (ft_free(&com, 0));
	if ((len = ft_strlen(com[1])) > COMMENT_LENGTH)
		return (ft_free(&com, 1));
	if (!(ft_strcpy(header->comment, com[1])))
		return (ft_free(&com, 2));
	ft_putstr_fd(header->comment, file.fdwrite);
	while (++len < (COMMENT_LENGTH + 7))
		ft_putchar_fd(0, file.fdwrite);
	ft_free_tab2d(&com);
	return (1);
}

int			ft_recupcom(t_header *header, char *line, t_file file)
{
	char	**split;
	int		lensplit;
	int		len;
	int		i;

	lensplit = 0;
	if (!(split = ft_splitwhitespaces(line)))
		return (0);
	if (ft_strcmp(split[0], COMMENT_CMD_STRING))
		return (ft_freecom(&split, 0, NULL));
	if (!(split[1]))
		return (ft_free(&split, 0));
	while (split[lensplit])
		lensplit++;
	len = ft_strlen(split[lensplit - 1]);
	if (split[1][0] != '\"' || split[lensplit - 1][len - 1] != '\"')
		return (ft_freecom(&split, 1, "Comment"));
	i = ft_com(line, header, file);
	ft_free_tab2d(&split);
	return (i);
}

static int	ft_name(char *line, t_header *header, t_file file)
{
	char	**name;
	int		len;

	name = NULL;
	if (!(name = ft_strsplit(line, '\"')))
		return (0);
	if (!name[1])
		return (ft_free(&name, 0));
	if ((len = ft_strlen(name[1])) > PROG_NAME_LENGTH)
		return (ft_free(&name, 1));
	if (!(ft_strcpy(header->prog_name, name[1])))
		return (ft_free(&name, 2));
	ft_putstr_fd(header->prog_name, file.fdwrite);
	while (++len < (PROG_NAME_LENGTH + 8))
		ft_putchar_fd(0, file.fdwrite);
	ft_free_tab2d(&name);
	return (1);
}

int			ft_recupname(t_header *header, char *line, t_file file)
{
	char	**split;
	int		lensplit;
	int		len;
	int		i;

	lensplit = 0;
	if (!(split = ft_splitwhitespaces(line)))
		return (0);
	if (ft_strcmp(split[0], NAME_CMD_STRING))
		return (ft_freecom(&split, 0, NULL));
	if (!(split[1]))
		return (ft_free(&split, 0));
	while (split[lensplit])
		lensplit++;
	len = ft_strlen(split[lensplit - 1]);
	if (split[1][0] != '\"' || split[lensplit - 1][len - 1] != '\"')
		return (ft_freecom(&split, 1, "Name"));
	i = ft_name(line, header, file);
	ft_free_tab2d(&split);
	return (i);
}
