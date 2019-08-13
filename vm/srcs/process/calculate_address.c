/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_address.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 18:04:25 by bopopovi          #+#    #+#             */
/*   Updated: 2019/08/13 14:37:02 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

unsigned int	calculate_address(t_vm *vm, t_proc *proc, t_op op,
		unsigned int p[2])
{
	unsigned int	addr;
	short			added;

	added = ((short)((short)p[0] + (short)p[1]));
	if (op.addr_restrict)
		added = added % IDX_MOD;
	addr = proc->pc + added;
	dbg_print_addr(vm->options & OPTD, op, proc, p);
	return (addr);
}
