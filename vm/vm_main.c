/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:21:58 by vlambert          #+#    #+#             */
/*   Updated: 2019/06/19 16:40:33 by vlambert         ###   ########.fr       */
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
	ft_printf("options : %#b  dump %d\nPlayer number1 %d\n%s\n%s\n%d\nPlayer number2 %d\n%s\n%s\n%d\n",
		vm.options, vm.cycles_limit, vm.players[0].number, vm.players[0].name, vm.players[0].comment, vm.players[0].size, vm.players[1].number, vm.players[1].name, vm.players[1].comment, vm.players[1].size);
}
