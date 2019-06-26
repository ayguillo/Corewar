/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:21:58 by vlambert          #+#    #+#             */
/*   Updated: 2019/06/26 09:54:36 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"
#include "../libft/libft.h"

/*
** Check errors.h for message max size ERR_MSG_SIZE
*/
void	init_err(t_vm *vm, int *err)
{
	*err = 0;
	ft_strcpy(vm->err[USAGE], "Usage: ./corewar [-d -v -V] \
[-dump nbr_cycles] [[-n number] champion1.cor] ...\n-d: Debug mode\
\n-v: Verbose mode\n-V: Visual mode\n");
	ft_strcpy(vm->err[ERR_DBLDUMP], "More than one dump precised\n");
	ft_strcpy(vm->err[ERR_BADARG], "Unknown argument\n");
	ft_strcpy(vm->err[ERR_DUMPVAL], "Dump nbr_cycles is lower than \
one or missing with option -dump\n");
	ft_strcpy(vm->err[ERR_BADNBR], "The player number is lower than 1 or \
missing or the same than another player\n");
	ft_strcpy(vm->err[ERR_TWONBR], "Two player number were precised \
for a single player\n");
	ft_strcpy(vm->err[ERR_OPEN], ": Can't access the champ\n");
	ft_strcpy(vm->err[ERR_CHAMP], " doesn't seem to be a champion \
(bad magic number or invalid header)\n");
	ft_strcpy(vm->err[ERR_MALLOC], " Malloc error\n");
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
