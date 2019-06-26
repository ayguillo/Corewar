/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:21:58 by vlambert          #+#    #+#             */
/*   Updated: 2019/06/26 15:40:43 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"
#include "../libft/libft.h"

static void	player_print_info(t_player *player)
{
	ft_printf("Player [ %d ] :\n", player->number);
	ft_printf("\tname\t: %s\n", player->name);
	ft_printf("\tcomment\t: %s\n", player->comment);
	ft_printf("\tsize\t: %d\n", player->size);
	ft_printf("\tR1\t: %d\n\n", player->regs[0]);
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
}
