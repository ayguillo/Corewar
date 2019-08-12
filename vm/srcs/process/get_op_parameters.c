/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_op_parameters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:18:39 by bopopovi          #+#    #+#             */
/*   Updated: 2019/08/12 10:56:33 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

static bool l_dbg = 1;

int		get_parameter(t_vm *vm, t_proc *proc, t_param *param, t_op op)
{
	if (param->type == DIR_CODE)
	{
		local_dbg(l_dbg, "%02x (DIR)\n", param->type);
		param->val = read_from_vm(vm, proc->op_pc, op.dir_type == 0 ? 4 : 2);
		return (op.dir_type == 0 ? 4 : 2);
	}
	else if (param->type == IND_CODE)
	{
		local_dbg(l_dbg, "%02x (IND)\n", param->type);
		param->val = read_from_vm(vm, proc->op_pc, IND_SIZE);
		return (IND_SIZE);
	}
	else if (param->type == REG_CODE)
	{
		local_dbg(l_dbg, "%02x (REG)\n", param->type);
		param->val = read_from_vm(vm, proc->op_pc, T_REG);
		return (T_REG);
	}
	else
	{
		local_dbg(l_dbg, "{red}%02x (UNKNOWN){eoc}\n", param->type);
		return (0); /* UNDEFINED PARAM TYPE */
	}
}

int		get_op_parameters(t_vm *vm, t_proc *proc, t_param *params, t_op op)
{
	int		i;
	int		parameter_size;
	int		ret;

	i = 0;
	ret = 0;
	parameter_size = 0;
	dbg_print_params_head(l_dbg);
	while (i < op.arg_nbr)
	{
		if ((parameter_size = get_parameter(vm, proc, &params[i], op)) <= 0)
			ret = -1;
			proc->op_pc += parameter_size;
		local_dbg(l_dbg, "\n");
		i++;
	}
	if (params[3].type != 0)
		ret = -1;
	return (ret);
}
