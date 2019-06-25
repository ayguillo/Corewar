/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:21:58 by vlambert          #+#    #+#             */
/*   Updated: 2019/06/25 18:02:51 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"
#include "../libft/libft.h"

void	init_err(t_vm *vm, int *err)
{
	*err = 0;
	ft_strcpyfast(vm->err[USAGE], USAGE_MSG, ERR_MSG_SIZE);
	ft_strcpyfast(vm->err[ERR_DBLDUMP], ERR_DBLDUMP_MSG, ERR_MSG_SIZE);
	ft_strcpyfast(vm->err[ERR_BADARG], ERR_BADARG_MSG, ERR_MSG_SIZE);
	ft_strcpyfast(vm->err[ERR_DUMPVAL], ERR_DUMPVAL_MSG, ERR_MSG_SIZE);
	ft_strcpyfast(vm->err[ERR_BADNBR], ERR_BADNBR_MSG, ERR_MSG_SIZE);
	ft_strcpyfast(vm->err[ERR_TWONBR], ERR_TWONBR_MSG, ERR_MSG_SIZE);
	ft_strcpyfast(vm->err[ERR_OPEN], ERR_OPEN_MSG, ERR_MSG_SIZE);
	ft_strcpyfast(vm->err[ERR_CHAMP], ERR_CHAMP_MSG, ERR_MSG_SIZE);
}

static void		player_print_info(t_player *player)
{
	ft_printf("Player [ %d ] :\n", player->number);
	ft_printf("\tname\t: %s\n", player->name);
	ft_printf("\tcomment\t: %s\n", player->comment);
	ft_printf("\tsize\t: %d\n\n", player->size);
}

int		main(int ac, char *av[])
{
	t_vm	vm;
	int		err;

	ft_bzero(&vm, sizeof(vm));
	init_err(&vm, &err);
	if (ac < 3 || (err = options(ac, av, &vm)))
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
