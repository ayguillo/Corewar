/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_jmpz.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:23:44 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/19 15:56:54 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

__attribute__((unused))static bool l_dbg = 1;

void	op_jmpz(__attribute__((unused))t_vm *vm, t_proc *process,
	t_param *params, __attribute__((unused))t_op op)
{
	unsigned int	jump_address;

	local_dbg(l_dbg, "{magenta}EXECUTING OP_JMPZ{eoc}\n");
	/* Subject docs states (PC + (VAL % IDX_MOD)) but it doesn't work */
	jump_address = ((process->pc + params[0].val) % MEM_SIZE) /*% IDX_MOD*/;
	local_dbg(l_dbg, "Jump address : 0x%08x (%u)\n", jump_address, jump_address);
	local_dbg(l_dbg, "(PC [%u]) + (P1 [%u] %% IDX) %% MEM_SIZE\n", process->pc,
		params[0].val);
	if (process->carry == 1)
	{
		process->op_pc = jump_address;
		local_dbg(l_dbg, "Jumped at address %d\n", jump_address);
	}
	else
		local_dbg(l_dbg, "No carry me no jump\n");
	local_dbg(l_dbg, "{magenta}OP_JMPZ END{eoc}\n\n");
}
