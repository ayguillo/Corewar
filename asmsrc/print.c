/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 17:34:23 by ayguillo          #+#    #+#             */
/*   Updated: 2019/05/29 13:51:29 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"
#include "../libft/libft.h"
#include "../includes/asm.h"

static int	ft_readn(t_file file, char **line, int *ret)
{
	*ret = ft_gnl(file.fdopen, line);
	if (!(*line) || *line[0] == 0)
	{
		ft_strdel(line);
		return (0);
	}
	return (1);
}

static void	print_magic(t_header *header, t_file file)
{
	int				i;
	unsigned char	*cast;
	int				j;

	i = COREWAR_EXEC_MAGIC;
	header->magic = i;
	cast = (unsigned char *)&i;
	j = 4;
	while (--j >= 0)
		ft_putchar_fd(cast[j], file.fdwrite);
}

int			printfile(t_header *header, t_file file)
{
	int		ret;
	char	*line;

	line = NULL;
	print_magic(header, file);
	if ((ret = ft_gnl(file.fdopen, &line)) <= 0)
	{
		ft_strdel(&line);
		return (0);
	}
	while (ret > 0 && line[0] == '\n')
		ret = ft_gnl(file.fdopen, &line);
	if ((ft_recupname(header, line, file)) <= 0)
		return (0);
	if (!(ft_readn(file, &line, &ret)))
		return (0);
	if (ft_recupcom(header, line, file) <= 0)
		return (0);
	return (1);
}
