/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:24:02 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/01 20:17:37 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/proc.h"

static bool l_dbg = 1;

void	op_and(t_vm *vm, t_proc *process)
{
	t_param			params[3];
	int				op_result;
	char			ocp;

	local_dbg(l_dbg, "Instruction op_and()\n");
	ft_bzero(params, sizeof(t_param) * 3);
	process->dir_size = T_LDIR;
	process->pc += T_OPCODE;
	ocp = read_byte_from_vm(vm, process->pc);
	process->pc += T_OCP;
	set_params_from_ocp(params, ocp, 3);
	local_dbg(l_dbg, "Getting Parameters for op_and()\n", NULL);
	process->pc += get_instruction_parameter(vm, process, &params[0]);
	process->pc += get_instruction_parameter(vm, process, &params[1]);
	process->pc += get_instruction_parameter(vm, process, &params[2]);
	op_result = (params[0].val & params[1].val);
	if (op_result == 0)
		process->carry = 1;
	write_to_register(process, params[2].val, op_result);
	local_dbg(l_dbg, "Written value '%d' to register %d\n", op_result, params[2].val);
}
