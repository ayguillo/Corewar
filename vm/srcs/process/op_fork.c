/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 18:11:27 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/17 21:27:56 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"
#include "vm.h"

__attribute__((unused))static bool l_dbg = 1;

void	op_fork(t_vm *vm, t_proc *process, t_param *params, t_op op)
{
	unsigned int fork_addr;

	(void)op;
	local_dbg(l_dbg, "{magenta}EXECUTING OP_FORK{eoc}\n");
	fork_addr = (process->pc + (params[0].val % IDX_MOD)) % MEM_SIZE;
	local_dbg(l_dbg, "Fork address : 0x%08x (%u)\n", fork_addr, fork_addr);
	local_dbg(l_dbg, "(PC [%u] + ((P1 [%u] %% (IDX %u)) %% MEM_SIZE)",
		process->pc, params[0].val, IDX_MOD);
	add_process(vm, process->player, fork_addr, process);
	local_dbg(l_dbg, "{magenta}OP_FORK END{eoc}\n\n");
}
