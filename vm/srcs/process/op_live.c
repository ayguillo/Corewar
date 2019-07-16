/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:24:08 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/15 16:54:35 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

static bool l_dbg = 1;

void	op_live(t_vm *vm, t_proc *process, t_op op)
{
	int		live_id;
	int		player;

	(void)op;
	local_dbg(l_dbg, "Instruction op_live()\n");
	process->pc += T_OPCODE;
	live_id = read_from_vm(vm, process->pc, T_LDIR);
	process->pc += T_LDIR;
	if ((player = get_player_nbr(vm, live_id)) >= 0)
		set_player_alive(vm, process, player);
	local_dbg(l_dbg, "Set player %d as alive\n", live_id);
}
