/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 04:23:30 by bopopovi          #+#    #+#             */
/*   Updated: 2019/09/10 08:45:34 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

static void	verbose_lld(t_proc *proc, t_param *params)
{
	if (VERBOSE_ON)
		ft_printf("P %4d | lld %d r%d\n", proc->number,
			params[0].val, params[1].val);
}

static void	verbose_lldi(t_proc *proc, t_param *params)
{
	if (VERBOSE_ON)
		ft_printf("P %4d | lldi %d %d r%d\n", proc->number,
			params[0].val, params[1].val, params[2].val);
}

void		op_lld(t_vm *vm, t_proc *process, t_param *params, t_op op)
{
	unsigned int reg_dest;
	unsigned int load;

	(void)op;
	local_dbg(vm->options & OPTD, "{magenta}EXECUTING OP_LLD{eoc}\n");
	load = 0;
	if (params[0].type == DIR_CODE)
		load = params[0].val;
	else if (params[0].type == IND_CODE)
		load = read_from_vm(vm, process->pc + (params[0].val), IND_SIZE);
	reg_dest = params[1].val;
	local_dbg(vm->options & OPTD, "Destination register : %d\n", reg_dest);
	write_to_register(process, reg_dest, load, vm);
	process_set_carry(process, op, load, vm);
	local_dbg(vm->options & OPTD, "{magenta}OP_LLD END{eoc}\n\n");
	verbose_lld(process, params);
}

void		op_lldi(t_vm *vm, t_proc *process, t_param *params, t_op op)
{
	unsigned int reg_dest;
	unsigned int write;
	unsigned int src[2];

	(void)op;
	local_dbg(vm->options & OPTD, "{magenta}EXECUTING OP_LLDI{eoc}\n");
	ft_bzero(src, sizeof(int) * 2);
	if (params[0].type == REG_CODE)
		read_from_register(process, params[0].val, &src[0], vm);
	else if (params[0].type == IND_CODE)
		src[0] = read_from_vm(vm, process->pc + params[0].val,
			op.dir_type == 0 ? 4 : 2);
	else if (params[0].type == DIR_CODE)
		src[0] = params[0].val;
	if (params[1].type == REG_CODE)
		read_from_register(process, params[1].val, &src[1], vm);
	else if (params[1].type == DIR_CODE)
		src[1] = params[1].val;
	reg_dest = params[2].val;
	local_dbg(vm->options & OPTD, "Destination register : %d\n", reg_dest);
	local_dbg(vm->options & OPTD, "Value to be written :\n");
	write = read_from_vm(vm, process->pc + (src[0] + src[1]), sizeof(int));
	write_to_register(process, reg_dest, write, vm);
	process_set_carry(process, op, write, vm);
	local_dbg(vm->options & OPTD, "{magenta}OP_LLDI END{eoc}\n\n");
	verbose_lldi(process, params);
}
