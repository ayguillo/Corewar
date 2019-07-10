/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:27:05 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/10 17:35:30 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "options.h"

void	set_player_alive(t_vm *vm, t_proc *process, int player)
{
	vm->players[player].period_lives += 1;
	vm->last_player_alive = player;
	process->period_lives += 1;
	vm->period_lives += 1;
	if (vm->options & OPTV)
		print_action(vm, process, "life");
}
