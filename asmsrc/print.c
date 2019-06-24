/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 17:34:23 by ayguillo          #+#    #+#             */
/*   Updated: 2019/06/24 17:20:20 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"
#include "../libft/libft.h"
#include "../includes/asm.h"
#include <unistd.h>

int			printfile(t_header *header, t_file file, t_op **op)
{
	int		ret;
	char	*line;
	int		lenname;
	int		lencom;

	line = NULL;
	if ((ret = ft_gnl(file.fdopen, &line)) <= 0)
		return (ft_free(NULL, -1, &line, NULL));
	if ((ft_recupname(header, &line, &lenname)) <= 0)
		return (0);
	ret = ft_retgnl(file.fdopen, &line);
	if (ft_recupcom(header, &line, &lencom) <= 0)
		return (0);
	if (!(ft_readinst(file, ret, &line, op)))
		return (0);
	ft_strdel(&line);
	header->prog_size = ft_reversebyte(993, 4);// PROG_SIZE
	header->magic = ft_reversebyte(COREWAR_EXEC_MAGIC, 4);
	return (1);
}
