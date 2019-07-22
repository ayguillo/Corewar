/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_jmpz.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:23:44 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/20 17:34:36 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

__attribute__((unused))static bool l_dbg = 1;

void	op_jmpz(__attribute__((unused))t_vm *vm, t_proc *process,
	t_param *params, __attribute__((unused))t_op op)
{
	unsigned int	jmp_addr;

	dbg_print_instruction_head(l_dbg, "OP_ZJMP");
	/* Subject docs states (PC + (VAL % IDX_MOD)) but it doesn't work */
	jmp_addr = ((process->pc + params[0].val) % MEM_SIZE) /*% IDX_MOD*/;
	local_dbg(l_dbg, "%-15s: 0x%08x (%u)\n", "JMP_ADDR", jmp_addr, jmp_addr);
	if (process->carry == 1)
	{
		process->op_pc = jmp_addr;
		local_dbg(l_dbg, "Jumped at address %d\n", jmp_addr);
	}
	else
		local_dbg(l_dbg, "No carry me no jump\n");
}
