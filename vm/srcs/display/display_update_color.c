/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_update_color.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 18:45:31 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/30 21:59:00 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "display.h"

void	display_update_color(t_vm *vm, unsigned int start, int size,
	int player_id)
{
	int i;

	i = 0;
	if (vm->options & OPTZ)
	{
		start %= MEM_SIZE;
		while (i < size)
		{
			vm->display.color_map[start + i].code = (player_id + 1);
			i++;
		}
	}
}
