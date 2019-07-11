/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchlabel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 11:39:35 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/11 16:17:50 by ayguillo         ###   ########.fr       */
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

int			ft_searchlabel(t_asm *tasm)
{
	t_op	*tmp;
	int		i;

	tmp = tasm->op;
	while (tmp->next)
	{
		i = 0;
		while (i < 3)
		{
			if (tmp->searchlabel[i])
				ft_searchlabel1(&tasm->op, tmp, i);
			++i;
		}
		if (tmp->addr > CHAMP_MAX_SIZE)
			return (ft_free(NULL, 4, &tasm->gnl, NULL));
		tmp = tmp->next;
	}
	return (1);
}
