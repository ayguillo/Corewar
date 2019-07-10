/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 09:33:37 by vlambert          #+#    #+#             */
/*   Updated: 2019/07/10 11:35:37 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "options.h"
#include "../libft/libft.h"

void	intro_champs(t_vm *vm)
{
	int i;

	if (vm->options & OPTMAJV || vm->options & OPTZ)
		return ;
	i = 0;
	ft_printf("Introducing contestants...\n");
	while (i < vm->players_nbr)
	{
		ft_printf("* Player %d, wheighing %d bytes, \"%s\" (\"%s\") !\n",
			i + 1, vm->players[i].size, vm->players[i].name,
			vm->players[i].comment);
		++i;
	}
	ft_putchar('\n');
}

void	print_action(t_vm *vm, t_proc *proc, char *action)
{
	if (!(vm->options & OPTV))
		return ;
	ft_printf("Processus %d from player %d is doing a %s",
		proc->number, proc->player, action);
}

void	print_winner(t_vm *vm)
{
	print_arena_govisu(vm, 1);
	if (vm->options & OPTZ || vm->options & OPTMAJV)
		return ;
	if (vm->last_player_alive != -1)
	{
		ft_printf("AND THE WINNER IS...\n");
		ft_printf(".:! Player %d: \"%s\" !:.\n", (vm->last_player_alive) + 1,
			vm->players[vm->last_player_alive].name);
	}
	else
		ft_printf("It's a draw\nChamps were weaker than ever\n");
}
