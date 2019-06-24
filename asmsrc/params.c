/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 12:14:08 by ayguillo          #+#    #+#             */
/*   Updated: 2019/06/24 14:21:43 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"
#include "../includes/asm.h"
#include "../libft/libft.h"

void	ft_paramlive(char **split, t_op *op)
{
	char			**dirsplit;
	t_op			*tmp;
	unsigned int	param;
	char			**label;

	tmp = op;
	if (split[1] && split[1][0] != DIRECT_CHAR)
	{
		ft_printf("%s is not a direct, dit you mean %c%s ?\n", split[1],
				DIRECT_CHAR, split[1]);
		return ;
	}
	if (split[1] && split[1][1] == LABEL_CHAR)
	{
		if (!(label = ft_strsplit(split[1], LABEL_CHAR)))
			return ;
		param = ft_paramlabel(tmp, label[1]);
	}
	else
	{
		if (!(dirsplit = ft_strsplit(split[1], DIRECT_CHAR)))
			return ;
		param = ft_atol(dirsplit[0]);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->inst = LIVE;
	ft_fillparam1(op, DIR_SIZE, DIR_CODE, param);
}
