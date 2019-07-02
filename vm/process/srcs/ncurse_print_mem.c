/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurse_print_mem.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 19:10:48 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/02 17:04:24 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/proc.h"

#include <stdlib.h>

void	win_print_memory(t_win *memory_win, unsigned char *memory, int position)
{
	int i;
	int j;
	int pc;

	j = 1;
	i = 2;
	pc = 0;
	wmove(memory_win->win, j, i);
	while (j + 1 < memory_win->height)
	{
		while (i + 2 < (memory_win->width))
		{
			if (pc % MEM_SIZE == position % MEM_SIZE)
			{
				init_pair(1, COLOR_RED, COLOR_BLACK);
				wattron(memory_win->win, COLOR_PAIR(1));
				wprintw(memory_win->win, "%02hhx", memory[pc]);
				wattroff(memory_win->win, COLOR_PAIR(1));
			}
			else
				wprintw(memory_win->win, "%02hhx", memory[pc]);
			pc++;
			i += 3;
			if (i + 2 < memory_win->width)
				wmove(memory_win->win, j, i);
		}
		if (pc >= MEM_SIZE || j + 1 >= memory_win->height)
			break ;
		j++;
		i = 2;
		if (j + 1 < (memory_win->height))
			wmove(memory_win->win, memory_win->y + j, i);
	}
	wrefresh(memory_win->win);
	//refresh();
}

void init_memory_win(t_win *memory)
{
	ft_bzero(memory, sizeof(*memory));
	memory->x = 0;
	memory->y = 0;
	memory->height = MEM_SIZE / 64; // 64 lines
	memory->width = ((MEM_SIZE / 64) * 3); // 64 pairs of chars + spaces
	memory->win = newwin(memory->height, memory->width, 0, 0);
	box(memory->win, 0, 0);
	wrefresh(memory->win);
}

void	display_memory(t_vm *vm, int pc)
{
	char c;

	if (VISU_ON)
	{
		win_print_memory(&vm->display.memory, vm->mem, pc);
		(void)vm;
		//move(0, 0);
		//refresh();
		while ((c = wgetch(vm->display.memory.win)) != 'q')
			;
	}
}
