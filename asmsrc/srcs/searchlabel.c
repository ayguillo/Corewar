/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchlabel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 11:39:35 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/10 12:48:22 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/libft.h"

static void	ft_searchlabel1(t_op **op, t_op *search, int i)
{
	t_op	*tmp;

	tmp = *op;
	while (tmp->next)
	{
		if (tmp->label)
			if (!(ft_strcmp(search->searchlabel[i], tmp->label)))
			{
				search->param[i] = ((search->addr - tmp->addr + MEM_SIZE)
						% MEM_SIZE);
				break ;
			}
		tmp = tmp->next;
	}
}

void		ft_searchlabel(t_op **op)
{
	t_op	*tmp;
	int		i;

	tmp = *op;
	while (tmp->next)
	{
		i = 0;
		while (i < 3)
		{
			if (tmp->searchlabel[i])
				ft_searchlabel1(op, tmp, i);
			++i;
		}
		tmp = tmp->next;
	}
}
