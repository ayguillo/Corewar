/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 04:14:59 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/20 16:48:07 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

__attribute__((unused))static bool l_dbg = 1;

void	op_add(__attribute__((unused))t_vm *vm, t_proc *process,
	t_param *params, t_op op)
{
	int op_result;

	dbg_print_instruction_head(l_dbg, "OP_ADD");
	op_result = (params[0].val + params[1].val);
	dbg_print_math(l_dbg, '+', params[0].val, params[1].val, op_result);
	write_to_register(process, params[2].val, op_result);
	process_set_carry(process, op, op_result);
}
