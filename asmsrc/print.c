/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 17:34:23 by ayguillo          #+#    #+#             */
/*   Updated: 2019/06/03 14:58:39 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"
#include "../libft/libft.h"
#include "../includes/asm.h"
#include <unistd.h>

static int		ft_readn(t_file file, char **line, int *ret)
{
	ft_strdel(line);
	*ret = ft_gnl(file.fdopen, line);
	if (!(*line) || *line[0] == 0)
	{
		ft_strdel(line);
		return (0);
	}
	return (1);
}

unsigned int	ft_reversebyte(unsigned int byte)
{
	unsigned int	revbyte;
	int				i;
	
	i = 3;
	while (i >= 0)
	{
		((char*)(&revbyte))[i] = ((char*)(&byte))[0];
		byte = byte >> 8;
		i--;
	}
	return (revbyte);
}

int			printfile(t_header *header, t_file file)
{
	int		ret;
	char	*line;
	int		lenname;
	int		lencom;

	line = NULL;
	if ((ret = ft_gnl(file.fdopen, &line)) <= 0)
		return (ft_free(NULL, -1, &line));
	if ((ft_recupname(header, &line, &lenname)) <= 0)
		return (0);
	if (!(ft_readn(file, &line, &ret)))
		return (0);
	if (ft_recupcom(header, &line, &lencom) <= 0)
		return (0);
	if (!(ft_inst(file, ret, &line)))
		return (0);
	ft_strdel(&line);
	header->prog_size = ft_reversebyte(23);
	header->magic = ft_reversebyte(COREWAR_EXEC_MAGIC);
	write(file.fdwrite, header, sizeof(t_header));
	return (1);
}
