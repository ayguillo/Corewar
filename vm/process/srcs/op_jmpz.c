/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_jmpz.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:23:44 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/01 20:18:03 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/proc.h"

static bool l_dbg = 1;

void	op_jmpz(t_vm *vm, t_proc *process)
{
	short		jump_address;

	local_dbg(l_dbg, "Instruction op_jmpz()\n");
	jump_address = read_from_vm(vm, process->pc + T_OPCODE, T_SDIR);
	jump_address = (process->pc + jump_address) % MEM_SIZE;
	if (process->carry == 1)
	{
		process->pc = jump_address;
		local_dbg(l_dbg, "Jumped at address %d\n", jump_address);
	}
	else
	{
		local_dbg(l_dbg, "No carry me no jump\n");
		process->pc += T_OPCODE;
		process->pc += T_SDIR;
	}
}
