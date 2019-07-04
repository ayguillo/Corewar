/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 17:34:23 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/04 16:52:59 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"
#include "../libft/libft.h"
#include "../includes/asm.h"
#include <unistd.h>

static int	readerror(t_gnl *gnl)
{
	ft_dprintf(2, "Read() failed or empty command line %i\n", gnl->nbline);
	ft_strdel(&(gnl->line));
	return (0);
}

int			printfile(t_header *header, t_file file, t_op **op)
{
	int		lenname;
	int		lencom;
	t_op	*tmp;
	t_gnl	gnl;

	gnl.line = NULL;
	gnl.nbline = 0;
	if (!(ft_retgnl(file.fdopen, &gnl, 1)))
		return (readerror(&gnl));
	if ((ft_recupname(header, &gnl, &lenname)) <= 0)
		return (0);
	if (!(ft_retgnl(file.fdopen, &gnl, 1)))
		return (readerror(&gnl));
	if (ft_recupcom(header, &gnl, &lencom) <= 0)
		return (0);/*
	if (!(ft_readinst(file, ret, &line, op)))
		return (0);
	ft_strdel(&line);
	tmp = *op;
	while (tmp->next)
		tmp = tmp->next;
	header->prog_size = ft_reversebyte(tmp->addr, 4);
	header->magic = ft_reversebyte(COREWAR_EXEC_MAGIC, 4);*/
	return (1);
}
