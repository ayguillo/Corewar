/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchlabel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 11:39:35 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/10 11:59:30 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/libft.h"

static void	ft_searchlabel1(t_op **op, t_op *search)
{
	t_op	*tmp;

	tmp = *op;
	while (tmp->next)
	{
		if (tmp->label)
			if (!(ft_strcmp(tmp->searchlabel1, tmp->label)))
			{
				search->param1 = ((search->addr - tmp->addr + MEM_SIZE)
						% MEM_SIZE);
				break ;
			}
		tmp = tmp->next;
	}
}

static void	ft_searchlabel2(t_op **op, t_op *search)
{
	t_op	*tmp;

	tmp = *op;
	while (tmp->next)
	{
		if (tmp->label)
			if (!(ft_strcmp(tmp->searchlabel2, tmp->label)))
			{
				search->param2 = ((search->addr - tmp->addr + MEM_SIZE)
						% MEM_SIZE);
				break ;
			}
		tmp = tmp->next;
	}
}
static void	ft_searchlabel3(t_op **op, t_op *search)
{
	t_op	*tmp;

	tmp = *op;
	while (tmp->next)
	{
		if (tmp->label)
			if (!(ft_strcmp(tmp->searchlabel3, tmp->label)))
			{
				search->param3 = ((search->addr - tmp->addr + MEM_SIZE)
						% MEM_SIZE);
				break ;
			}
		tmp = tmp->next;
	}
}

void		ft_searchlabel(t_op **op)
{
	t_op *tmp;

	tmp = *op;
	while (tmp->next)
	{
		if (tmp->searchlabel1)
			ft_searchlabel1(op, tmp);
		if (tmp->searchlabel2)
			ft_searchlabel2(op, tmp);
		if (tmp->searchlabel3)
			ft_searchlabel3(op, tmp);
		tmp = tmp->next;
	}
}
