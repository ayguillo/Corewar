/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 04:18:50 by bopopovi          #+#    #+#             */
/*   Updated: 2019/09/10 08:45:22 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

static void	verbose_sub(t_proc *proc, t_param *params)
{
	if (VERBOSE_ON)
	{
		ft_printf("P %4d | sub r%d r%d r%d\n", proc->number, params[0].val,
			params[1].val, params[2].val);
	}
}

void		op_sub(t_vm *vm, t_proc *process, t_param *params, t_op op)
{
	unsigned int	op_result;
	unsigned int	p[2];

	dbg_print_instruction_head(vm->options & OPTD, "OP_SUB");
	p[0] = read_parameter(vm, process, op, &params[0]);
	p[1] = read_parameter(vm, process, op, &params[1]);
	op_result = (p[0] - p[1]);
	dbg_print_math(vm->options & OPTD, '-', p, op_result);
	if (write_to_register(process, params[2].val, op_result, vm) == 0)
	{
		process_set_carry(process, op, op_result, vm);
		verbose_sub(process, params);
	}
}
