/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_code.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 11:37:55 by vlambert          #+#    #+#             */
/*   Updated: 2019/07/16 15:01:36 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "../../libft/libft.h"
#include <unistd.h>
#include <stdio.h>

int		accept_d4(int inst)
{
	if (inst == LIVE || inst == AND || inst == OR || inst == XOR || inst == LD
			|| inst == LLD)
		return (1);
	return (0);
}

void	write_args(t_file *file, t_op *tmp, int i)
{
	unsigned int	to_write;

	to_write = ft_reversebyte(tmp->param[i], 4);
	if (tmp->code[i] == REG_CODE)
		write(file->fdwrite, &to_write, 1);
	else if (tmp->code[i] == DIR_CODE && accept_d4(tmp->inst))
		write(file->fdwrite, &to_write, 4);
	else
		write(file->fdwrite, &to_write, 2);
}

void	write_code(t_file *file, t_op *op)
{
	t_op			*tmp;
	int				i;
	char			opc;

	tmp = op;
	while (tmp)
	{
		if (tmp->inst != 0)
		{
			opc = 0;
			i = 0;
			write(file->fdwrite, &(tmp->inst), 1);
			if (tmp->inst != LIVE && tmp->inst != ZJMP && tmp->inst != FORK
					&& tmp->inst != LFORK)
			{
				opc = ft_opc(tmp->code);
				write(file->fdwrite, &opc, 1);
			}
			while (i < tmp->nbarg)
			{
				write_args(file, tmp, i);
				++i;
			}
		}
		tmp = tmp->next;
	}
}
