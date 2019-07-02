/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_register.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:12:00 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/01 20:23:54 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/proc.h"

int		read_from_register(t_proc *proc, int id)
{
	int read;

	if (id > REG_NUMBER)
		; /* PROC SET STATUS ERROR INVALID REG */
	read = proc->regs[id];
	return (read);
}
