/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 17:34:23 by ayguillo          #+#    #+#             */
/*   Updated: 2019/05/28 17:41:00 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"
#include "../libft/libft.h"
#include "../includes/asm.h"

static void	print_magic(header_t *header, t_all all)
{
	int				i;
	unsigned char	*cast;
	int				j;

	i = COREWAR_EXEC_MAGIC;
	header->magic = i;
	cast = (unsigned char *)&i;
	j = 4;
	while (--j >= 0)
		ft_putchar_fd(cast[j], all.fdwrite);
}

static int	ft_name(char *split, header_t *header, t_all all)
{
	char	**name;
	int		len;

	name = NULL;
	if (!(name = ft_strsplit(split, '\"')))
		return (0);
	if (!name[0])
	{
		ft_putstr("Empty name\n");
		return (-1);
	}
	if ((len = ft_strlen(name[0])) > 128)
	{
		ft_putstr("Champion name too long (Max length 128)\n");
		return (-1);
	}
	if (!(ft_strcpy(header->prog_name, name[0])))
		return (0);
	ft_putstr_fd(header->prog_name, all.fdwrite);
	if (len < 128)
	{
		while (++len < 128)
			ft_putchar_fd(0, all.fdwrite);
	}
	return (1);
}

static int	ft_recupname(header_t *header, char *line, t_all all)
{
	char	**split;
	int		len;

	if (!(split = ft_splitwhitespaces(line)))
		return (0);
	if (ft_strcmp(split[0], NAME_CMD_STRING))
	{
		ft_printf("Command '%s' invalid\n", split[0]);
		return (-1);
	}
	len = ft_strlen(split[1]);
	if (split[1][0] != '\"' || split[1][len - 1] != '\"')
	{
		ft_putstr("Name is not a string\n");
		return (-1);
	}
	return (ft_name(split[1], header, all));
}

int			printfile(header_t *header, t_all all)
{
	int		ret;
	char	*line;

	line = NULL;
	print_magic(header, all);
	if ((ret = ft_gnl(all.fdopen, &line)) <= 0)
	{
		ft_strdel(&line);
		return (0);
	}
	while (ret > 0 && line[0] == '\n')
		ret = ft_gnl(all.fdopen, &line);
	if (!(line) || line[0] == 0)
	{
		ft_strdel(&line);
		return (0);
	}
	if ((ft_recupname(header, line, all)) <= 0)
		return (0);
	return (1);
}
