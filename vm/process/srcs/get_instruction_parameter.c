/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instruction_parameter.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:18:39 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/01 20:14:19 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/proc.h"

static bool l_dbg = 1;

/* Could be improved with function pointers */
int		get_instruction_parameter(t_vm *vm, t_proc *proc, t_param *param)
{
	int addr;

	addr = 0;
	if (param->type == DIR_CODE)
	{
		local_dbg(l_dbg, "\tParameter code : %02x (DIR)\n", param->type);
		param->val = read_from_vm(vm, proc->pc, proc->dir_size);
		return (proc->dir_size);
	}
	else if (param->type == IND_CODE)
	{
		local_dbg(l_dbg, "\tParameter code : %02x (IND)\n", param->type);
		addr = read_from_vm(vm, proc->pc, T_IND);
		param->val = read_from_vm(vm, addr, T_LDIR);
		return (T_IND);
	}
	else if (param->type == REG_CODE)
	{
		local_dbg(l_dbg, "\tParameter code : %02x (IND)\n", param->type);
		addr = read_from_vm(vm, proc->pc, T_REG);
		param->val = read_from_register(proc, addr);
		return (T_REG);
	}
	else
	{
		local_dbg(l_dbg, "\tParameter code : %02x (UNKNOWN)\n", param->type);
		return (ERROR); /* UNDEFINED PARAM TYPE */
	}
}
