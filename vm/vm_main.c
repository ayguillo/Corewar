/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:21:58 by vlambert          #+#    #+#             */
/*   Updated: 2019/06/18 14:06:35 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"
#include "../includes/errors.h"
#include "../libft/libft.h"

void    init_err(t_vm *vm)
{
    ft_strcpyfast(vm->err[USAGE], "Usage: ./corewar [-d -v -V] [-dump nbr_cycles] [[-n number] champion1.cor] ...\n-d: Debug mode\n-v: Verbose mode\n-V: Visual mode\n", 500);
    ft_strcpyfast(vm->err[ERR_DBLDUMP], "There are multiple dump precised\n", 500);
    ft_strcpyfast(vm->err[ERR_BADARG], "One argument doesn't exist\n", 500);
    ft_strcpyfast(vm->err[ERR_DUMPVAL], "The dump nbr_cycles is lower than one or missing\n", 500);
    ft_strcpyfast(vm->err[ERR_BADNBR], "The player number is lower than 1 or missing or the same than another player\n", 500);
    ft_strcpyfast(vm->err[ERR_TWONBR], "Two player number were precised for a single player\n", 500);
}

int     main(int ac, char *av[])
{
    t_vm    vm;
    int     err;
    
    ft_bzero(&vm, sizeof(vm));
    init_err(&vm);
    if (ac < 3)
        return (ft_printf("%s", vm.err[0]));
    if ((err = options(ac, av, & vm)))
        return (ft_printf("%#b\nCorewar arg error: %s%s", vm.options, vm.err[err], vm.err[USAGE]));
    ft_printf("options : %#b\nPlayer number1 %d\nPlayer number2 %d\n", vm.options, vm.players[0].number, vm.players[1].number);
}