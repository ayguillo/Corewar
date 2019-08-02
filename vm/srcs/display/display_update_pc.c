/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_update_pc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 19:00:54 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/30 21:58:38 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "display.h"

void	remove_old_pc(t_vm *vm, unsigned int old_pc, int player_id)
{
	char	bit_mask;

	bit_mask = 1;
	bit_mask <<= player_id;
	bit_mask ^= 0xff;
	vm->display.color_map[old_pc].pc &= bit_mask;
}

void	add_new_pc(t_vm *vm, unsigned int new_pc, int player_id)
{
	vm->display.color_map[new_pc].pc |= (1 << player_id);
}

void	display_update_pc(t_vm *vm, unsigned int old_pc, unsigned int new_pc,
	int player_id)
{
	if (vm->options & OPTZ)
	{
		remove_old_pc(vm, old_pc, player_id);
		add_new_pc(vm, new_pc, player_id);
	}
}
