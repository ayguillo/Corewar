/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 09:01:50 by vlambert          #+#    #+#             */
/*   Updated: 2019/06/26 13:08:18 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"
#include "../libft/libft.h"
#include "stdlib.h"

int		add_process(t_vm *vm, t_player *player, unsigned int pc)
{
	t_proc	*new;
	t_proc	*tmp;

	if (!(new = ft_memalloc(sizeof(t_proc))))
	{
		ft_putstr_fd("vm_process.c: add_process:", 2);
		return (ERR_MALLOC);
	}
	new->pc = pc % MEM_SIZE;
	if (!(player->proc))
	{
		player->proc = new;
		new->number = 1;
	}
	else
	{
		tmp = player->proc;
		while (tmp->next)
			tmp = tmp->next;
		new->number = tmp->number + 1;
		tmp->next = new;
	}
	return (0);
}

void	kill_unactive_processes(t_player *player, int end)
{
	t_proc	*tmp;
	t_proc	*tmp_previous;
	t_proc	*to_free;

	tmp = player->proc;
	to_free = NULL;
	tmp_previous = NULL;
	while (tmp)
	{
		if (tmp->period_lives == 0 || end)
			to_free = tmp;
		else
			tmp->period_lives = 0;
		if (player->proc == to_free)
			player->proc = player->proc->next;
		else if (to_free && tmp_previous)
			tmp_previous->next = to_free->next;
		else
			tmp_previous = tmp;
		tmp = tmp->next;
		if (to_free)
			ft_memdel((void **)&to_free);
	}
}
