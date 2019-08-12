/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 04:21:22 by bopopovi          #+#    #+#             */
/*   Updated: 2019/08/12 15:45:12 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

void	op_xor(t_vm *vm, t_proc *process, t_param *params, t_op op)
{
	unsigned int op_result;
	unsigned int src_1;
	unsigned int src_2;

	dbg_print_instruction_head(vm->options & OPTD, "OP_XOR");
	src_1 = read_parameter(vm, process, op, &params[0]);
	src_2 = read_parameter(vm, process, op, &params[1]);
	op_result = (src_1 ^ src_2);
	dbg_print_math(vm->options & OPTD, '^', src_1, src_2, op_result);
	write_to_register(process, params[2].val, op_result, vm);
	process_set_carry(process, op, op_result, vm);
}
