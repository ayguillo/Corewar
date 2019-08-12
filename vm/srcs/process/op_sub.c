/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 04:18:50 by bopopovi          #+#    #+#             */
/*   Updated: 2019/08/12 15:45:08 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

void	op_sub(t_vm *vm, t_proc *process, t_param *params, t_op op)
{
	unsigned int	op_result;
	unsigned int	p1;
	unsigned int	p2;

	dbg_print_instruction_head(vm->options & OPTD, "OP_SUB");
	p1 = read_parameter(vm, process, op, &params[0]);
	p2 = read_parameter(vm, process, op, &params[1]);
	op_result = (p1 - p2);
	dbg_print_math(vm->options & OPTD, '-', p1, p2, op_result);
	write_to_register(process, params[2].val, op_result, vm);
	process_set_carry(process, op, op_result, vm);
}
