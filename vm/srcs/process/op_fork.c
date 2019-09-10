/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 18:11:27 by bopopovi          #+#    #+#             */
/*   Updated: 2019/09/10 08:44:00 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"
#include "vm.h"

static void	verbose_fork(t_proc *proc, int addr, int real_addr)
{
	if (VERBOSE_ON)
	{
		ft_printf("P %4d | fork %hd (%hd)\n", proc->number, addr, real_addr);
	}
}

static void	verbose_lfork(t_proc *proc, int addr, int real_addr)
{
	if (VERBOSE_ON)
	{
		ft_printf("P %4d | lfork %hd (%hd)\n", proc->number, addr, real_addr);
	}
}

void		op_fork(t_vm *vm, t_proc *process, t_param *params, t_op op)
{
	unsigned int	fork_addr;
	int				err;

	(void)op;
	dbg_print_instruction_head(vm->options & OPTD, "OP_FORK");
	fork_addr = (process->pc + (short)((short)params[0].val % IDX_MOD))
		% MEM_SIZE;
	local_dbg(vm->options & OPTD, "%-15s: 0x%08x (%u)\n", "FORK_ADDR",
		fork_addr, fork_addr);
	verbose_fork(process, params[0].val, (process->pc
				+ (short)((short)params[0].val % IDX_MOD)));
	if ((err = add_process(vm, process->player, fork_addr, process)))
		ft_putstr_fd(vm->err[err], 2);
}

void		op_lfork(t_vm *vm, t_proc *process, t_param *params, t_op op)
{
	unsigned int	fork_addr;
	int				err;

	(void)op;
	dbg_print_instruction_head(vm->options & OPTD, "OP_LFORK");
	fork_addr = (unsigned short)(process->pc + params[0].val) % MEM_SIZE;
	local_dbg(vm->options & OPTD, "%-15s: 0x%08x (%u)\n", "FORK_ADDR",
		fork_addr, fork_addr);
	verbose_lfork(process, params[0].val, (process->pc + params[0].val));
	if ((err = add_process(vm, process->player, fork_addr, process)))
		ft_putstr_fd(vm->err[err], 2);
}
