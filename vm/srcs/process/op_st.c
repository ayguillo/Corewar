/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:23:51 by bopopovi          #+#    #+#             */
/*   Updated: 2019/09/06 02:27:19 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

static void	verbose_st(t_proc *proc, t_param *params)
{
	if (VERBOSE_ON)
	{
		ft_printf("P %4d | st r%d %hd\n", proc->number, params[0].val,
			params[1].val);
	}
}

static void	verbose_sti(t_proc *proc, int reg, int p1, int p2)
{
	if (VERBOSE_ON)
	{
		ft_printf("P %4d | sti r%d %hd %hd\n", proc->number, reg,
			p1, p2);
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
			p1, p2, p1 + p2, proc->pc + ((p1 + p2) % IDX_MOD));
	}
}

void	op_st(t_vm *vm, t_proc *process, t_param *params, t_op op)
{
	unsigned int	reg_load;
	int				store_addr;

	(void)op;
	store_addr = 0;
	dbg_print_instruction_head(vm->options & OPTD, "OP_ST");
	if (read_from_register(process, params[0].val, &reg_load, vm))
		return ;
	if (params[1].type == REG_CODE)
		write_to_register(process, params[1].val, reg_load, vm);
	else if (params[1].type == IND_CODE)
	{
		store_addr = (process->pc + (short)((short)params[1].val % IDX_MOD)
			% MEM_SIZE);
		write_to_vm(vm, store_addr, reg_load, process->player);
	}
	verbose_st(process, params);
}

void	op_sti(t_vm *vm, t_proc *process, t_param *params, t_op op)
{
	unsigned int	store_addr;
	unsigned int	reg_load;
	unsigned int	p[2];

	ft_bzero(p, sizeof(int) * 2);
	dbg_print_instruction_head(vm->options & OPTD, "OP_STI");
	if (params[0].val < 1 || params[0].val > REG_NUMBER)
		return ;
	if (read_from_register(process, params[0].val, &reg_load, vm))
		return ;
	p[0] = read_parameter(vm, process, op, &params[1]);
	p[1] = read_parameter(vm, process, op, &params[2]);
	store_addr = calculate_address(vm, process, op, p);
	write_to_vm(vm, store_addr, reg_load, process->player);
	verbose_sti(process, params[0].val, p[0], p[1]);
}
