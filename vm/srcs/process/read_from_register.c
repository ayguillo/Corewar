/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_register.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:12:00 by bopopovi          #+#    #+#             */
/*   Updated: 2019/08/13 12:06:41 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

unsigned int	read_from_register(t_proc *proc, int id, t_vm *vm)
{
	unsigned int read;

	read = 0;
	if (id < 1 || id > REG_NUMBER)
		local_dbg(vm->options & OPTD, "{red}REG_READ INVALID ID : '%d'{eoc}\n",
			id);
	else
	{
		read = proc->regs[id - 1];
		local_dbg(vm->options & OPTD, "%-15s: 0x%08x (%u) <- ", "REG_READ",
			read, read);
		local_dbg(vm->options & OPTD, "REG %d\n", id);
	}
	return (read);
}
