/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:27:05 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/17 21:21:56 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "options.h"

__attribute__((unused))static bool l_dbg = 1;

void	set_player_alive(t_vm *vm, t_proc *process, int player)
{
	local_dbg(l_dbg, "Setting player %d as alive\n", player);
	vm->players[player].period_lives += 1;
	vm->last_player_alive = player;
	process->period_lives += 1;
	vm->period_lives += 1;
	if (vm->options & OPTV)
		print_action(vm, process, "life");
}
