/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:24:02 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/17 21:14:04 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

__attribute__((unused))static bool l_dbg = 1;

void	op_and(__attribute__((unused))t_vm *vm, t_proc *process,
	t_param *params, t_op op)
{
	int				op_result;

	local_dbg(l_dbg, "{magenta}EXECUTING OP_AND{eoc}\n");
	op_result = (params[0].val & params[1].val);
	local_dbg(l_dbg, "Value : 0x%08x (0x%08x AND 0x%08x)\n", op_result,
		params[0].val, params[1].val);
	write_to_register(process, params[2].val, op_result);
	process_set_carry(process, op, op_result);
	local_dbg(l_dbg, "{magenta}OP_AND END{eoc}\n\n");
}
