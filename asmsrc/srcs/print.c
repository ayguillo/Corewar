/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 17:34:23 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/16 15:50:03 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"
#include "../libft/libft.h"
#include "../includes/asm.h"

static int	readerror(t_asm *tasm)
{
	ft_dprintf(2, "Read() failed or empty command line %i\n", tasm->gnl.nbline);
	ft_strdel(&(tasm->gnl.line));
	return (0);
}

int			printfile(t_header *header, t_asm *tasm)
{
	int		lenname;
	int		lencom;
	t_op	*tmp;

	if ((ft_retgnl(tasm, 1) <= 0 && !(readerror(tasm)))
		|| ft_recup(header, tasm, &lenname, NAME) <= 0
		|| (ft_retgnl(tasm, 1) <= 0 && !(readerror(tasm)))
		|| ft_recup(header, tasm, &lencom, COM) <= 0
		|| !(ft_readinst(tasm)))
		return (0);
	tmp = tasm->op;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!tmp)
	{
		ft_dprintf(2, "No instruction\n");
		return (0);
	}
	header->prog_size = ft_reversebyte(tmp->addr + tmp->size, 4);
	header->magic = ft_reversebyte(COREWAR_EXEC_MAGIC, 4);
	return (1);
}
