/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 19:10:48 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/05 22:30:13 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"
#include "options.h"

#include <stdlib.h>

void	win_print_memory(t_win *memory_win, unsigned char *memory, int position)
{
	int i;
	int pc;

	i = 0;
	pc = 0;
	wmove(memory_win->contents, 0, 0);
	while (pc < MEM_SIZE)
	{
		if (pc % MEM_SIZE == position % MEM_SIZE)
		{
			init_pair(1, COLOR_RED, COLOR_BLACK);
			wattron(memory_win->contents, COLOR_PAIR(1));
			wprintw(memory_win->contents, "%02hhx", memory[pc]);
			wattroff(memory_win->contents, COLOR_PAIR(1));
		}
		else
			wprintw(memory_win->contents, "%02hhx", memory[pc]);
		i += 2;
		if (i + 1 < (MEM_W - 4) && pc + 1 < MEM_SIZE)
		{
			i++;
			wprintw(memory_win->contents, " ");
		}
		else
			i = 0;
		pc++;
	}
}

void	display_memory(t_vm *vm, int pc)
{
	char c;

	if (vm->options & OPTZ)
	{
		win_print_memory(&vm->display.memory, vm->mem, pc);
		wrefresh(vm->display.memory.contents);
		while ((c = wgetch(vm->display.memory.contents)) != 'n')
			;
	}
}
