/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 20:38:51 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/17 22:20:49 by bopopovi         ###   ########.fr       */

#include "proc.h"

static bool l_dbg = 1;

void	(*g_op_fptr[12])(t_vm*, t_proc*, t_param*, t_op) =
{
	&op_live,
	&op_ld,
	&op_st,
	NULL,
	NULL,
	&op_and,
	NULL,
	NULL,
	&op_jmpz,
	&op_ldi,
	&op_sti,
	&op_fork
};

void	exec_op(unsigned char opcode, t_vm *vm, t_proc *process, t_op op)
{
	if (opcode > 0 && opcode <= 11)
		g_op_fptr[opcode - 1](vm, process, op);
}

int		process_execute(t_vm *vm, t_proc *process)
{
	unsigned int	pc;
	unsigned char	opcode;

	pc = process->pc % MEM_SIZE;
	opcode = vm->mem[pc];
	//local_dbg(l_dbg, "MEMORY STATE :\n");
	//tmp_print_mem(vm->mem, MEM_SIZE / 4);
	if (process->waiting > 0)
		process->waiting -= 1;
	else if (process->waiting == 0)
	{
		local_dbg(l_dbg, "Instruction opcode : %02x\n", opcode);
		exec_op(opcode, vm, process, g_op_tab[opcode - 1]);
		process->waiting = -1;
		local_dbg(l_dbg, "PC state at instruction end : %d\n", process->pc);
	}
	else if (process->waiting == -1)
		process->waiting = g_op_tab[opcode - 1].cycles;
	return (0);
}
