/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 04:14:59 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/18 04:18:09 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

__attribute__((unused))static bool l_dbg = 1;

void	op_add(__attribute__((unused))t_vm *vm, t_proc *process,
	t_param *params, t_op op)
{
	int op_result;

	local_dbg(l_dbg, "{magenta}EXECUTING OP_ADD{eoc}\n");
	op_result = (params[0].val + params[1].val);
	local_dbg(l_dbg, "Value : 0x%08x (0x%08x + 0x%08x)\n", op_result,
		params[0].val, params[1].val);
	write_to_register(process, params[2].val, op_result);
	process_set_carry(process, op, op_result);
	local_dbg(l_dbg, "{magenta}OP_ADD END{eoc}\n\n");
}
