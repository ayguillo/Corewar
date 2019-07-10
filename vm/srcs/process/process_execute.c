/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 20:38:51 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/10 19:53:21 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

static bool l_dbg = 1;

void	(*g_op_set[11])(t_vm*, t_proc*) =
{
	&op_live,
	NULL,
	NULL,
	NULL,
	NULL,
	&op_and,
	NULL,
	NULL,
	&op_jmpz,
	NULL,
	&op_sti
};

int		op_cycles[16] =
{
	10,
	10,
	10,
	10,
	10,
	10,
	10,
	10,
	10,
	10,
	10,
	10,
	10,
	10,
	10,
	10,
};

void	exec_op(unsigned char opcode, t_vm *vm, t_proc *process)
{
	if (opcode > 0 && opcode <= 11)
		g_op_set[opcode - 1](vm, process);
}

int		get_cycles_for_opcode(char opcode)
{
	return (op_cycles[opcode - 1]);
}

int		process_execute(t_vm *vm, t_proc *process)
{
	unsigned int	pc;
	unsigned char	opcode;

	pc = process->pc % MEM_SIZE;
	opcode = vm->mem[pc];
	//ft_putendl(" EXECUTING ");
	local_dbg(l_dbg, "MEMORY STATE :\n");
	tmp_print_mem(vm->mem, MEM_SIZE / 4);
	if (process->waiting > 0)
		process->waiting -= 1;
	else if (process->waiting == 0)
	{
		local_dbg(l_dbg, "Instruction opcode : %02x\n", opcode);
		exec_op(opcode, vm, process);
		process->waiting = -1;
		local_dbg(l_dbg, "PC state at instruction end : %d\n", process->pc);
	}
	else if (process->waiting == -1)
		process->waiting = get_cycles_for_opcode(opcode);
	return (0);
}
