/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_register.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:12:00 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/17 20:29:53 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

static bool l_dbg = 1;

int		read_from_register(t_proc *proc, int id)
{
	int read;

	read = 0;
	if (id < 1 || id > REG_NUMBER)
		local_dbg(l_dbg, "{red}REG_READ INVALID ID : '%d'{eoc}\n", id);
	else
	{
		read = proc->regs[id - 1];
		local_dbg(l_dbg, "REG_READ value 0x%08x from register %d\n", read, id);
	}
	return (read);
}
