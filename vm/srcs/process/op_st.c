/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:23:51 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/12 21:12:41 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

static bool l_dbg = 1;

void	op_sti(t_vm *vm, t_proc *process, t_op op)
{
	int				initial_pc;
	t_param			params[3];
	int				store_addr;
	int				reg_load;
	char			ocp;

	local_dbg(l_dbg, "Instruction op_sti()\n");
	initial_pc = process->pc;
	ft_bzero(params, sizeof(t_param) * 3);
	process->dir_size = T_SDIR;
	process->pc += T_OPCODE;
	ocp = read_byte_from_vm(vm, process->pc);
	if (ocp_match_instruction_params(op, ocp))
	{
		process->pc += T_OCP;
		set_params_from_ocp(params, ocp, 3);
		local_dbg(l_dbg, "Getting Parameters for op_sti()\n", NULL);
		process->pc += get_instruction_parameter(vm, process, &params[0]);
		process->pc += get_instruction_parameter(vm, process, &params[1]);
		process->pc += get_instruction_parameter(vm, process, &params[2]);
		store_addr = initial_pc + (params[1].val + params[2].val);
		reg_load = read_from_register(process, params[0].val);
		write_to_vm(vm, store_addr, reg_load, T_LDIR);
		process_set_carry(process, reg_load);
		local_dbg(l_dbg, "Write value '%d' at address %d\n", reg_load, store_addr);
	}
}
