/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_arena.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:19:47 by vlambert          #+#    #+#             */
/*   Updated: 2019/07/04 16:08:22 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/vm.h"
#include "../includes/options.h"
#include "../libft/color.h"

static void	print_infos_govisu(t_vm *vm)
{
	int		i;

	i = 0;
	ft_printf("---CYCLES---\nCycles: %d\nPeriod cycles: %d / %d\n", vm->cycles,
		vm->period_cycles, vm->cycle_to_die);
	ft_printf("\n---LAST LIFE---\n%s\n",
		vm->players[vm->last_player_alive].name);
	ft_printf("\n---PLAYERS---\n");
	while (i < vm->players_nbr)
	{
		ft_printf("\n---PLAYER[%d]---\n", vm->players[i].number);
		ft_printf("Name: %s\n", vm->players[i].name);
		ft_printf("Period lives: %d\n", vm->players[i].period_lives);
		ft_printf("Last period lives: %d\n", vm->players[i].last_p_lives);
		ft_printf("Number of alive process: %d\n", vm->players[i].alive_proc);
		i++;
	}
	ft_printf(";");
}

static int	check_pc(t_vm *vm, t_proc *tmp, int i)
{
	if (i == tmp->pc && tmp->player == 0)
	{
		ft_printf("RE");
		return (1);
	}
	if (i == tmp->pc && tmp->player == 1)
	{
		ft_printf("GR");
		return (1);
	}
	if (i == tmp->pc && tmp->player == 2)
	{
		ft_printf("PU");
		return (1);
	}
	if (i == tmp->pc && tmp->player == 3)
	{
		ft_printf("YE");
		return (1);
	}
	return (0);
}

void		print_arena_govisu(t_vm *vm, int end)
{
	int		i;
	t_proc	*tmp;

	if (!(vm->options & OPTMAJV))
		return ;
	i = 0;
	while (i < MEM_SIZE)
	{
		tmp = vm->proc;
		while (tmp && !check_pc(vm, tmp, i))
			tmp = tmp->next;
		ft_printf("%02x", vm->mem[i]);
		i++;
	}
	ft_printf(";");
	if (end)
		ft_printf("The winner is: \nPlayer[%d]: %s;", 
			vm->players[vm->last_player_alive].number,
			vm->players[vm->last_player_alive].name);
	else
		print_infos_govisu(vm);
}

int			create_arena(t_vm *vm)
{
	int		i;
	int		start;

	i = 0;
	while (i < vm->players_nbr)
	{
		start = i * MEM_SIZE / vm->players_nbr;
		ft_strcpyfast((char *)vm->mem + start, (char *)vm->players[i].code,
			vm->players[i].size);
		if (add_process(vm, i, start, NULL) == ERR_MALLOC)
		{
			while (i--)
				kill_unactive_processes(vm, 1);
			return (ERR_MALLOC);
		}
		++i;
	}
	return (0);
}
