/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 09:08:54 by vlambert          #+#    #+#             */
/*   Updated: 2019/07/02 17:04:56 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"
#include "../libft/libft.h"

static int	process_cycle(t_vm *vm)
{
	t_proc *tmp;

	tmp = vm->proc;
	while (tmp)
	{
		if (tmp->waiting == 0 || tmp->waiting == -1)
		{
			process_execute(vm, tmp);
			//vm->proc->period_lives += 1;
		}
		else
			tmp->waiting -= 1;
		tmp = tmp->next;
	}
	return (0);
}

static int	new_period(t_vm *vm)
{
	int	i;

	i = vm->players_nbr;
	while (i--)
	{
		vm->players[i].last_p_lives = vm->players[i].period_lives;
		vm->players[i].period_lives = 0;
	}
	vm->period_lives = 0;
	vm->period_cycles = 0;
	kill_unactive_processes(vm, 0);
	return (0);
}

int			game_cycle(t_vm *vm)
{
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->checks = MAX_CHECKS;
	if (!vm->cycles_limit)
		vm->cycles_limit = -1;
	while (vm->proc && ((vm->cycles += 1) != vm->cycles_limit
			|| vm->cycles_limit == -1) && vm->cycle_to_die > 0)
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
			new_period(vm);
		}
	}
	return (0);
}
