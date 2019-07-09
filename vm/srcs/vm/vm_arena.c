/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_arena.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:19:47 by vlambert          #+#    #+#             */
/*   Updated: 2019/07/09 15:28:35 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/vm.h"
#include "../includes/options.h"
#include "../libft/color.h"
#include <errno.h>
#include <stdio.h>

static void	check_pipe_errors(t_vm *vm)
{
	if (errno)
	{
		kill_unactive_processes(vm, 1);
		perror("Corewar:");
		exit(-1);
	}
}

static void	print_infos_govisu(t_vm *vm)
{
	int		i;

	i = 0;
	ft_printf("---CYCLES---\nCycles: %d\nPeriod cycles: %d / %d\n", vm->cycles,
		vm->period_cycles, vm->cycle_to_die);
	ft_printf("\n---LAST LIFE---\n%s\n",
		(vm->last_player_alive != -1) ?
			vm->players[vm->last_player_alive].name : "Nobody");
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

void		check_colors(unsigned int i, t_vm *vm, const char *color_code)
{
	t_proc	*tmp;
	char	color[3];

	tmp = vm->proc;
	color[2] = 0;
	while (tmp && tmp->pc != i)
		tmp = tmp->next;
	if (tmp)
		color[0] = color_code[tmp->player];
	else
		color[0] = 'Z';
	if (vm->mem_infos_code[i] != -1)
		color[1] = color_code[(int)(vm->mem_infos_code[i])];
	else
		color[1] = 'Z';
	ft_putstr(color);
}

void		print_arena_govisu(t_vm *vm, int end)
{
	unsigned int	i;

	if (!(vm->options & OPTMAJV))
		return ;
	i = 0;
	while (i < MEM_SIZE)
	{
		check_colors(i, vm, "RGPY");
		ft_printf("%02x", vm->mem[i]);
		i++;
	}
	ft_printf(";");
	check_pipe_errors(vm);
	if (end && vm->last_player_alive != -1)
		ft_printf("The winner is: \nPlayer[%d]: %s;",
			vm->players[vm->last_player_alive].number,
			vm->players[vm->last_player_alive].name);
	else
		print_infos_govisu(vm);
	check_pipe_errors(vm);
}

int			create_arena(t_vm *vm)
{
	int		i;
	int		start;

	i = 0;
	if (vm->options & OPTMAJV)
		ft_memset((void*)vm->mem_infos_code, -1, MEM_SIZE);
	while (i < vm->players_nbr)
	{
		start = i * MEM_SIZE / vm->players_nbr;
		ft_strcpyfast((char *)vm->mem + start, (char *)vm->players[i].code,
			vm->players[i].size);
		if (vm->options & OPTMAJV)
			ft_memset((void*)vm->mem_infos_code + start, i,
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
