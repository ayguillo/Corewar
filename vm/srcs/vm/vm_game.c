/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 09:08:54 by vlambert          #+#    #+#             */
/*   Updated: 2019/07/10 10:43:03 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "../libft/libft.h"

static int	process_cycle(t_vm *vm)
{
	t_proc *tmp;

	tmp = vm->proc;
	while (tmp)
	{
		if (tmp->waiting == 0 || tmp->waiting == -1)
		{
			//process_execute(vm, tmp);
			tmp->period_lives += 1; //pour test
			tmp->pc = (tmp->pc + 1) % MEM_SIZE; //pour test
			vm->players[tmp->player].period_lives += 1;//pour test
			vm->period_lives += 1;//pour test
			vm->last_player_alive = tmp->player;//pour test
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
	vm->last_player_alive = -1;
	intro_champs(vm);
	while (vm->proc && ((vm->cycles += 1) != vm->cycles_limit
			|| vm->cycles_limit == 0) && vm->cycle_to_die > 0)
	{
		vm->period_cycles += 1;
		print_arena_govisu(vm, 0);
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
	print_arena_govisu(vm, 1);
	print_winner(vm);
	return (0);
}
