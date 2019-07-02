/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:24:08 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/01 20:18:22 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/proc.h"

static bool l_dbg = 1;

void	op_live(t_vm *vm, t_proc *process)
{
	int		live_id;

	local_dbg(l_dbg, "Instruction op_live()\n");
	process->pc += T_OPCODE;
	live_id = read_from_vm(vm, process->pc, T_LDIR);
	process->pc += T_LDIR;
	//if (player_exist(vm, live_id))
	//	set_player_alive(vm, live_id);
	/* Set player live settings */
	local_dbg(l_dbg, "Set player %d as alive\n", live_id);
}
