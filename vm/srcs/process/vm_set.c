/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:27:05 by bopopovi          #+#    #+#             */
/*   Updated: 2019/08/27 15:54:40 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "options.h"
#include "color.h"

void	set_player_alive(t_vm *vm, t_proc *process, int player)
{
	local_dbg(vm->options & OPTD, "Setting player %d as alive\n", player + 1);
	vm->players[player].period_lives += 1;
	vm->last_player_alive = player;
	if (vm->options & OPTV)
	{
		print_action(vm, process, "life");
		ft_putstr(vm->players[process->player].color);
		ft_printf("%s for %splayer %d%s\n",
			vm->players[process->player].color, vm->players[player].color,
			player + 1, _RESET_);
	}
}
