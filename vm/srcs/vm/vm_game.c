/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 09:08:54 by vlambert          #+#    #+#             */
/*   Updated: 2019/09/05 18:25:01 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

static int	process_cycle(t_vm *vm)
{
	t_proc				*tmp;

	tmp = vm->proc;
	if (vm->options & OPTZ)
		display_reset_pc_colors(vm);
	while (tmp)
	{
		if (tmp->waiting == 0 || tmp->waiting == -1)
			process_execute(vm, tmp);
		else
			tmp->waiting -= 1;
		if (vm->options & OPTZ)
			display_update_pc(vm, tmp->pc, tmp->player);
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
	kill_unactive_processes(vm, vm->cycle_to_die + CYCLE_DELTA > 0 ? 0 : 1);
	return (0);
}

int			game_cycle(t_vm *vm)
{
	intro_champs(vm);
	display_update(vm);
	while (((vm->cycles += 1) != vm->cycles_limit || vm->cycles_limit == 0)
			&& vm->proc)
	{
		if (vm->display.status.exit)
			return (0);
		vm->period_cycles += 1;
		print_arena_govisu(vm, 0);
		if (vm->period_cycles >= vm->cycle_to_die)
		{
			if ((vm->checks -= 1) == 0 || vm->period_lives >= NBR_LIVE)
			{
				vm->cycle_to_die -= CYCLE_DELTA;
				vm->checks = MAX_CHECKS;
			}
			new_period(vm);
		}
		process_cycle(vm);
		display_update(vm);
	}
	print_winner(vm);
	display_update(vm);
	return (0);
}
