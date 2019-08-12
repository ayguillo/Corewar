/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:49:39 by vlambert          #+#    #+#             */
/*   Updated: 2019/08/12 16:50:16 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

void	(*g_op_fptr[16])(t_vm*, t_proc*, t_param*, t_op) =
{
	&op_live,
	&op_ld,
	&op_st,
	&op_add,
	&op_sub,
	&op_and,
	&op_or,
	&op_xor,
	&op_jmpz,
	&op_ldi,
	&op_sti,
	&op_fork,
	&op_lld,
	&op_lldi,
	&op_lfork,
	&op_aff
};

int		process_param_types(t_vm *vm, t_proc *process, t_param *params, t_op op)
{
	char ocp;

	ocp = 0;
	if (op.has_ocp)
	{
		ocp = read_byte_from_vm(vm, process->op_pc);
		process->op_pc += T_OCP;
	}
	if (!op.has_ocp || ocp_match_instruction_params(op, ocp, vm))
	{
		set_params(params, op, ocp);
		return (1);
	}
	return (0);
}

void	execute_instruction(t_vm *vm, t_proc *process, t_op op)
{
	t_param		params[4];

	ft_bzero(params, sizeof(t_param) * 4);
	local_dbg(vm->options & OPTD, "{yellow}Instruction '%s' {eoc}\n",
		op.asm_name);
	process->op_pc += T_OPCODE;
	if (process_param_types(vm, process, params, op))
	{
		if (get_op_parameters(vm, process, params, op) >= 0)
		{
			g_op_fptr[(int)(op.opcode - 1)](vm, process, params, op);
			process->pc = process->op_pc % MEM_SIZE;
		}
		else
			process->pc = (process->op_pc) % MEM_SIZE;
	}
	else
		process->pc = (process->op_pc) % MEM_SIZE;
	process->op_pc = process->pc;
}

int		process_execute(t_vm *vm, t_proc *process)
{
	unsigned int	pc;
	unsigned char	opcode;

	pc = process->pc % MEM_SIZE;
	opcode = vm->mem[pc];
	if (process->waiting == -1 && (opcode <= 0 || opcode >= 17))
		process->pc = (process->pc + 1) % MEM_SIZE;
	else if (process->waiting == 0)
	{
		dbg_print_proc_head(vm->options & OPTD, vm, process);
		process->waiting = -1;
		process->op_pc = process->pc;
		execute_instruction(vm, process, g_op_tab[process->opcode - 1]);
		dbg_print_proc_end(vm->options & OPTD, vm, process);
	}
	else if (process->waiting == -1)
	{
		process->opcode = opcode;
		process->waiting = g_op_tab[opcode - 1].cycles - 2;
	}
	return (0);
}
