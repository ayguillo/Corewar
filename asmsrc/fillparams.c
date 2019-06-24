/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillparams.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 10:25:21 by ayguillo          #+#    #+#             */
/*   Updated: 2019/06/24 14:23:46 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/libft.h"

int		ft_paramlabel(t_op *op, char *label)
{
	t_op	*tmp;
	int		addr;
	int		filladdr;

	tmp = op;
	addr = -1;
	filladdr = 0;
	while (tmp->next)
	{
		filladdr += tmp->size;
		if (tmp->label)
			if (!ft_strcmp(tmp->label, label))
				addr = tmp->addr;
		tmp = tmp->next;
	}
	tmp->addr = filladdr;
	if (addr >= 0)
		return ((addr - filladdr + MEM_SIZE) % MEM_SIZE);
	return (0);
}

void	ft_fillparam1(t_op *op, int size, int code, unsigned int param1)
{
	t_op			*tmp;
	unsigned int	addr;

	tmp = op;
	addr = 0;
	while (tmp->next)
	{
		ft_printf("addr = %i\n", addr);
		addr += tmp->size + 1;
		tmp = tmp->next;
	}
	tmp->param1 = param1;
	if (addr != 0 && !(tmp->addr))
	{
		ft_printf("coucou\n");
		tmp->addr = addr;
	}
	tmp->size = size;
	tmp->code1 = code;
}
