/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_register.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 17:27:28 by bopopovi          #+#    #+#             */
/*   Updated: 2019/08/12 15:42:28 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

void	write_to_register(t_proc *process, int register_id, int write, t_vm *vm)
{
	/* ERROR CASE : Invalid register id */
	if (register_id < 1 || register_id > REG_NUMBER)
		local_dbg(vm->options & OPTD, "REG_WRITE INVALID ID : '%d'\n",
			register_id);
	else
	{
		local_dbg(vm->options & OPTD, "%-15s: 0x%08x (%u) -> ", "REG_WRITE",
			write, write);
		local_dbg(vm->options & OPTD, "REG %d\n", register_id);
		process->regs[register_id - 1] = write;
	}
}
