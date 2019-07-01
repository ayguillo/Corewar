/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 09:08:54 by vlambert          #+#    #+#             */
/*   Updated: 2019/07/01 14:43:55 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"
#include "../libft/libft.h"

static int	process_cycle(t_vm *vm)
{
	t_proc *tmp;

	while (tmp)
	{
		if (tmp->waiting == 0 || tmp->waiting == -1)
		{
			//call process function made by Bopopovic
		}
		tmp = tmp->next;
	}
}

int			game_cycle(t_vm *vm)
{
	vm->cycle_to_die = CYCLE_TO_DIE;
	if (!vm->cycles_limit)
		vm->cycles_limit = -1;
	while (vm->proc && ((vm->cycles += 1) != vm->cycles_limit
			|| vm->cycles_limit == -1))
	{
		vm->period_cycles += 1;
		process_cycle(vm);
		if (vm->period_cycles == vm->cycle_to_die)
		{
			if ((vm->checks -= 1) == 0 || vm->period_lives > NBR_LIVE)
			{
				vm->cycle_to_die -= CYCLE_DELTA;
				vm->checks = MAX_CHECKS;
			}
			kill_unactive_processes(vm, 0);
			vm->period_cycles = 0;
		}
	}
}