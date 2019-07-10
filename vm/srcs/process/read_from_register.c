/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_register.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:12:00 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/10 20:37:12 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

static bool l_dbg = 1;

int		read_from_register(t_proc *proc, int id)
{
	int read;

	if (id > REG_NUMBER)
		; /* PROC SET STATUS ERROR INVALID REG */
	local_dbg(l_dbg, "Reading from register %d\n", id);
	read = proc->regs[id];
	local_dbg(l_dbg, "Read value 0x%08x from register %d\n\n", read, id);
	return (read);
}
