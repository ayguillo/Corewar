/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_arena.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:19:47 by vlambert          #+#    #+#             */
/*   Updated: 2019/07/04 14:09:49 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/vm.h"
#include "../includes/options.h"
#include "../libft/color.h"

static void	print_color(t_vm *vm, char *color, int i)
{
	if (!(vm->options & OPTMAJV))
		ft_printf(color);
	else
	{
		if (!strcmp(color, _RED_))
			ft_printf("RE");
		if (!strcmp(color, _GREEN_))
			ft_printf("GR");
		if (!strcmp(color, _PURPLE_))
			ft_printf("PU");
		if (!strcmp(color, _YELLOW_))
			ft_printf("YE");
	}
	ft_printf("%02x", vm->mem[i]);
	if (!(vm->options & OPTMAJV))
		ft_printf(_RESET_);
}

static int	check_pc(t_vm *vm, t_proc *tmp, int i)
{
	if (i == tmp->pc && tmp->player == 0)
	{
		print_color(vm, _RED_, i);
		return (1);
	}
	if (i == tmp->pc && tmp->player == 1)
	{
		print_color(vm, _GREEN_, i);
		return (1);
	}
	if (i == tmp->pc && tmp->player == 2)
	{
		print_color(vm, _PURPLE_, i);
		return (1);
	}
	if (i == tmp->pc && tmp->player == 3)
	{
		print_color(vm, _YELLOW_, i);
		return (1);
	}
	return (0);
}

void		print_arena(t_vm *vm)
{
	int		i;
	t_proc	*tmp;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (!(vm->options & OPTMAJV) && !(i % 64) && i != 0)
			ft_printf("\n");
		else if (!(vm->options & OPTMAJV) && (i % 64))
			ft_printf(" ");
		tmp = vm->proc;
		while (tmp && !check_pc(vm, tmp, i))
			tmp = tmp->next;
		if (!tmp)
			ft_printf("%02x", vm->mem[i]);
		i++;
	}
	if (vm->options & OPTMAJV)
		ft_printf(";");
	else
		ft_printf("\n\n");
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
	print_arena(vm);
	return (0);
}
