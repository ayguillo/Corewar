/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 18:11:21 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/17 21:10:07 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

__attribute__((unused))static bool l_dbg = 1;

void	op_ld(__attribute__((unused))t_vm *vm, t_proc *process,
	t_param *params, __attribute__((unused))t_op op)
{
	int reg_dest;

	local_dbg(l_dbg, "{magenta}EXECUTING OP_LD{eoc}\n");
	reg_dest = params[1].val;
	local_dbg(l_dbg, "Destination register : %d\n", reg_dest);
	write_to_register(process, reg_dest, params[0].val);
	process_set_carry(process, op, params[0].val);
	local_dbg(l_dbg, "{magenta}OP_LD END{eoc}\n\n");
}

void	op_ldi(__attribute__((unused))t_vm *vm, t_proc *process,
	t_param *params, __attribute__((unused))t_op op)
{
	int		reg_dest;
	int		write;

	local_dbg(l_dbg, "{magenta}EXECUTING OP_LDI{eoc}\n");
	reg_dest = params[2].val;
	local_dbg(l_dbg, "Destination register : %d\n", reg_dest);
	local_dbg(l_dbg, "Value to be written :\n");
	write = read_from_vm(vm, (params[0].val + params[1].val), sizeof(int));
	write_to_register(process, reg_dest, write);
	process_set_carry(process, op, write);
	local_dbg(l_dbg, "{magenta}OP_LDI END{eoc}\n\n");
}
