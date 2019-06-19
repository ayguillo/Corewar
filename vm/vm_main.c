/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:21:58 by vlambert          #+#    #+#             */
/*   Updated: 2019/06/19 10:39:54 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"
#include "../libft/libft.h"

void	init_err(t_vm *vm)
{
	ft_strcpyfast(vm->err[USAGE], USAGE_MSG, ERR_MSG_SIZE);
	ft_strcpyfast(vm->err[ERR_DBLDUMP], ERR_DBLDUMP_MSG, ERR_MSG_SIZE);
	ft_strcpyfast(vm->err[ERR_BADARG], ERR_BADARG_MSG, ERR_MSG_SIZE);
	ft_strcpyfast(vm->err[ERR_DUMPVAL], ERR_DUMPVAL_MSG, ERR_MSG_SIZE);
	ft_strcpyfast(vm->err[ERR_BADNBR], ERR_BADNBR_MSG, ERR_MSG_SIZE);
	ft_strcpyfast(vm->err[ERR_TWONBR], ERR_TWONBR_MSG, ERR_MSG_SIZE);
}

int		main(int ac, char *av[])
{
	t_vm	vm;
	int		err;

	ft_bzero(&vm, sizeof(vm));
	init_err(&vm);
	if (ac < 3)
		return (ft_printf("%s", vm.err[USAGE]));
	if ((err = options(ac, av, &vm)))
		ft_printf("%#b\nCorewar arg error: %s%s", vm.options, vm.err[err], vm.err[USAGE]);
		return (-1);
	ft_printf("options : %#b  dump %d\nPlayer number1 %d\nPlayer number2 %d\n",
		vm.options, vm.cycles_limit, vm.players[0].number, vm.players[1].number);
}
