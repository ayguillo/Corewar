/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_arena.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:19:47 by vlambert          #+#    #+#             */
/*   Updated: 2019/06/26 16:06:58 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/vm.h"
#include "../libft/color.h"

void    print_arena(t_vm *vm)
{
    int i;

    i = 0;
    while (i < MEM_SIZE)
    {
        if (!(i % 64))
            ft_printf("\n");
        if (i == vm->players[0].proc->pc)
            ft_printf("%r%02x %r", _RED_, vm->mem[i], _RESET_);
        else if (i == vm->players[1].proc->pc)
            ft_printf("%r%02x %r", _GREEN_, vm->mem[i], _RESET_);
        else
            ft_printf("%r%02x %r", _BLUE_, vm->mem[i], _RESET_);
        i++;
    }
    ft_printf("\n\n");
}

int     create_arena(t_vm *vm)
{
    int i;
    int start;

    i = 0;
    while(i < vm->players_nbr)
    {
        start = i * MEM_SIZE / vm->players_nbr;
        ft_strcpyfast((char *)vm->mem + start, (char*)vm->players[i].code,
            vm->players[i].size);
        if (add_process(vm, &(vm->players[i]), start) == ERR_MALLOC)
        {
            while (i--)
                kill_unactive_processes(&(vm->players[i]), 1);
            return (ERR_MALLOC);
        }
        ++i;
    }
    return (0);
}