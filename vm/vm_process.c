/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 09:01:50 by vlambert          #+#    #+#             */
/*   Updated: 2019/06/21 16:47:46 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"
#include "../libft/libft.h"
#include "unistd.h"

int		add_proccess(t_vm *vm, t_player *player, unsigned int pc)
{
	t_proc	*new;
	t_proc	*tmp;

	if (!(new = malloc(sizeof(t_proc))))
	{
		ft_putstr_fd("vm_process.c: add_process:", 2);
		return (ERR_MALLOC);
	}
	ft_bzero(new, sizeof(t_proc));
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

void	clean_process(t_player *player)
{
	t_proc *tmp;

	tmp = player->proc;
	while (tmp)
	{

	}
}
