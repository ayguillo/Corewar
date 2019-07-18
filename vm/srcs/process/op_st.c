/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:23:51 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/17 21:11:54 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

__attribute__((unused))static bool l_dbg = 1;

void	op_sti(t_vm *vm, t_proc *process, t_param *params, t_op op)
{
	int				store_addr;
	int				reg_load;

	local_dbg(l_dbg, "{magenta}EXECUTING OP_STI :{eoc}\n");
	store_addr = process->pc + (params[1].val + params[2].val);
	local_dbg(l_dbg, "Store address :\n");
	local_dbg(l_dbg, "\t0x%0x (%u)\n", store_addr, store_addr);
	local_dbg(l_dbg, "\t(PC [%u]) + (P2 [%u]) + (P3 [%u])\n", process->pc,
		params[1].val, params[2].val);
	local_dbg(l_dbg, "Write value :\n\t");
	reg_load = read_from_register(process, params[0].val);
	local_dbg(l_dbg, "Writing 0x%08x from register %d to address %u\n",
		reg_load, params[0].val, (store_addr));
	write_to_vm(vm, store_addr, reg_load, 4, process->player);
	process_set_carry(process, op, reg_load);
	local_dbg(l_dbg, "{magenta}OP_STI END{eoc}\n\n");
}

void	op_st(t_vm *vm, t_proc *process, t_param *params, t_op op)
{
	int reg_load;

	(void)op;
	local_dbg(l_dbg, "{magenta}EXECUTING OP_ST :{eoc}\n");
	reg_load = read_from_register(process, params[0].val);
	if (params[1].type == REG_CODE)
	{
		local_dbg(l_dbg, "Got REG_CODE, value : %08x\n", reg_load);
		local_dbg(l_dbg, "Writing to register '%u'\n", params[1].val);
		write_to_register(process, params[1].val, params[0].val);
	}
	else if (params[1].type == IND_CODE)
	{
		local_dbg(l_dbg, "Got DIR_CODE, value : %08x\n", reg_load);
		local_dbg(l_dbg, "Writing to address '%u'\n", params[1].val % IDX_MOD);
		write_to_vm(vm, process->pc + (params[1].val % IDX_MOD), reg_load, 4,
			process->player);
	}
	local_dbg(l_dbg, "{magenta}OP_ST END{eoc}\n\n");
}
