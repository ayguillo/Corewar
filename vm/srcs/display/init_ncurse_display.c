/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ncurse_display.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 21:13:13 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/05 21:39:49 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "display.h"

void		new_win(t_win *new, int coord[4])
{
	ft_bzero(new, sizeof(*new));
	new->container = newwin(coord[0], coord[1], coord[2], coord[3]);
	box(new->container, 0, 0);
	new->contents = derwin(new->container, coord[0] - 2, coord[1] - 4, 1, 2);
	wrefresh(new->container);
	wrefresh(new->contents);
}

void		init_ncurse_display(t_vm *vm)
{
	initscr();
	noecho();
	curs_set(false);
	cbreak();
	start_color();
	refresh();
	ft_bzero(&vm->display, sizeof(vm->display));
	new_win(&vm->display.memory, (int[4]){MEM_H, MEM_W, 0, 0});
}
