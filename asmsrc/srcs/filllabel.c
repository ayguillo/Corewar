/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filllabel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:04:56 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/10 11:56:08 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/libft.h"

static int		ft_paramlabel(t_op *op, char *label, int nparam)
{
	t_op	*tmp;
	int		addr;
	int		filladdr;

	tmp = op;
	addr = -1;
	filladdr = 0;
	while (tmp->next)
	{
		filladdr += tmp->size + 1;
		if (tmp->label)
			if (!ft_strcmp(tmp->label, label))
			{
				addr = tmp->addr;
				break ;
			}
		tmp = tmp->next;
	}
	if (tmp->next == NULL)
	{
		if (nparam == 1)
			tmp->searchlabel1 = label;
		if (nparam == 2)
			tmp->searchlabel2 = label;
		if (nparam == 3)
			tmp->searchlabel3 = label;
	}
	if (addr >= 0)
		return ((addr - filladdr + MEM_SIZE) % MEM_SIZE);
	return (0);
}

unsigned int	ft_filllabel(t_op *op, char **split, int nparam)
{
	unsigned int	param;
	char			**label;
	char			**dirsplit;
	char			**indsplit;

	label = NULL;
	dirsplit = NULL;
	indsplit = NULL;
	if (split[nparam] && split[nparam][1] == LABEL_CHAR)
	{
		if (!(label = ft_strsplit(split[nparam], LABEL_CHAR)))
			return (0);
		param = ft_paramlabel(op, label[1], nparam);
	}
	else if (split[nparam][0] == DIRECT_CHAR)
	{
		if (!(dirsplit = ft_strsplit(split[nparam], DIRECT_CHAR)))
			return (0);
		param = ft_atui(dirsplit[0]);
	}
	else
	{
		if (!(label = ft_strsplit(split[nparam], LABEL_CHAR)))
			return (0);
		param = ft_paramlabel(op, label[0], nparam);
	}
	ft_free_tab2d(&dirsplit);
	ft_free_tab2d(&indsplit);
	ft_free_tab2d(&label);
	return (param);
}
