/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:23:51 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/15 17:46:10 by bopopovi         ###   ########.fr       */
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
	ft_bzero(params, sizeof(t_param) * op.arg_nbr);
	process->dir_size = op.dir_type == 0 ? 4 : 2;
	process->pc += T_OPCODE;
	ocp = read_byte_from_vm(vm, process->pc);
	if (ocp_match_instruction_params(op, ocp))
	{
		process->pc += T_OCP;
		set_params_from_ocp(params, ocp, op.arg_nbr);
		local_dbg(l_dbg, "Getting Parameters for op_sti()\n", NULL);
		get_op_parameters(vm, process, params, op);
		store_addr = initial_pc + (params[1].val + params[2].val);
		reg_load = read_from_register(process, params[0].val);
		write_to_vm(vm, store_addr, reg_load, T_LDIR);
		process_set_carry(process, reg_load);
		local_dbg(l_dbg, "Write value '%d' at address %d\n", reg_load, store_addr);
	}
	else
		local_dbg(l_dbg, "Parameters don't match ocp in op_sti.\n");
}
