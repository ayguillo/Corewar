/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:24:08 by bopopovi          #+#    #+#             */
/*   Updated: 2019/08/13 14:23:26 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

void	op_live(t_vm *vm, t_proc *process, t_param *params, t_op op)
{
	int		live_id;
	int		player;

	(void)op;
	dbg_print_instruction_head(vm->options & OPTD, "OP_LIVE");
	live_id = params[0].val;
	local_dbg(vm->options & OPTD, "Live id : %u\n", live_id);
	process->period_lives += 1;
	vm->period_lives += 1;
	if ((player = get_player_nbr(vm, live_id)) >= 0)
		set_player_alive(vm, process, player);
	else
		local_dbg(vm->options & OPTD, "{red}INVALID LIVE ID{eoc}\n");
}
