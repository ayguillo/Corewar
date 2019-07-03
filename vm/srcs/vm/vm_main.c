/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:21:58 by vlambert          #+#    #+#             */
/*   Updated: 2019/07/02 15:30:46 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"
#include "../libft/libft.h"
#include "../includes/options.h"

static void	player_print_info(t_player *player)
{
	ft_printf("Player [ %d ] :\n", player->number);
	ft_printf("\tname\t: %s\n", player->name);
	ft_printf("\tcomment\t: %s\n", player->comment);
	ft_printf("\tsize\t: %d\n", player->size);
	ft_printf("\tProcess en vie\t: %d\n\n", player->alive_proc);
}

static void	print_proc(t_vm *vm)
{
	t_proc *tmp;

	tmp = vm->proc;
	while (tmp)
	{
		ft_printf("\nprocess numero : %d\n", tmp->number);
		ft_printf("process player : %d\n", tmp->player);
		ft_printf("process pc : %d\n", tmp->pc);
		ft_printf("process R1 : %d\n", tmp->regs[0]);
		ft_printf("process periode lives : %d\n\n", tmp->period_lives);
		tmp = tmp->next;
	}
}

int			main(int ac, char *av[])
{
	t_vm	vm;
	int		err;

	ft_bzero(&vm, sizeof(vm));
	init_err(&vm, &err);
	if (ac < 3 || (err = options(ac, av, &vm))
		|| (err = create_arena(&vm)))
	{
		if (err)
			ft_putstr_fd(vm.err[err], 2);
		if (err < ERR_OPEN)
			ft_putstr_fd(vm.err[USAGE], 2);
		return (-1);
	}
	ft_printf("Options : %#b dump %d\n\n", vm.options, vm.cycles_limit);
	player_print_info(&vm.players[0]);
	player_print_info(&vm.players[1]);
	if (vm.options & OPTMAJV)
		ft_printf(";");
	game_cycle(&vm);
	print_arena(&vm);
	player_print_info(&vm.players[0]);
	player_print_info(&vm.players[1]);
	if (vm.options & OPTMAJV)
		ft_printf(";");
	kill_unactive_processes(&vm, 1);
}
