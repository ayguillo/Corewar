/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillparams.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 10:25:21 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/04 09:59:53 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/libft.h"

void			ft_fillparam1(t_op *op, int size, int code, unsigned int param1)
{
	t_op			*tmp;
	unsigned int	addr;

	tmp = op;
	addr = 0;
	while (tmp->next)
	{
		if (tmp->size != 0)
			addr += tmp->size + 1;
		tmp = tmp->next;
	}
	tmp->param1 = param1;
	tmp->addr = addr;
	tmp->size = size;
	tmp->code1 = code;
}

void			ft_fillparam2(t_op *op, int size, int code, unsigned int param2)
{
	t_op			*tmp;

	tmp = op;
	while (tmp->next)
		tmp = tmp->next;
	tmp->param2 = param2;
	tmp->size += size;
	tmp->code2 = code;
}

void			ft_fillparam3(t_op *op, int size, int code, unsigned int param3)
{
	t_op			*tmp;

	tmp = op;
	while (tmp->next)
		tmp = tmp->next;
	tmp->param3 = param3;
	tmp->size += size;
	tmp->code3 = code;
}
