/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 09:08:54 by vlambert          #+#    #+#             */
/*   Updated: 2019/06/28 11:39:10 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"
#include "../libft/libft.h"

static int	player_cycle(t_vm *vm)
{
	int		i;

	i = MAX_PLAYERS;
	while (i--)
	{
		if (vm->players[i].alive_proc)
		{
			if (vm->period_cycles == vm->cycle_to_die)
			{
				kill_unactive_processes(&(vm->players[i]), 0);
			}
		}
	}
}

int			game_cycle(t_vm *vm)
{
	vm->cycle_to_die = CYCLE_TO_DIE;
	if (!vm->cycles_limit)
		vm->cycles_limit = -1;
	while (vm->alive_proc && ((vm->cycles += 1) != vm->cycles_limit
			|| vm->cycles_limit == -1))
	{
		vm->period_cycles += 1;
		//player_cycle(t_vm *vm);

		if (vm->period_cycles == vm->cycle_to_die)
		{
			if (vm->period_lives > NBR_LIVE)
				
			vm->period_cycles = 1;
		}
	}
}