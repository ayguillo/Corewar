/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:19:58 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/15 17:12:58 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../../includes/proc.h"

void	tmp_print_mem(unsigned char *mem, unsigned int size)
{
	unsigned int i;

	i = 0;
	if (GLOBAL_DBG == 1 && VISU_ON == 0)
	{
		while (i < size)
		{
			fprintf(stderr, "%02x ", mem[i]);
			i++;
			if (i % 8 == 0)
				ft_putchar_fd('\n', 2);
		}
		ft_putendl_fd("\n", 2);
	}
}

void	local_dbg(bool debug, const char *fmt_msg, ...)
{
	va_list ap;

	if (debug == true && GLOBAL_DBG == 1 && VISU_ON == 0)
	{
		va_start(ap, fmt_msg);
		ft_vdprintf(2, fmt_msg, ap);
		va_end(ap);
	}
}


