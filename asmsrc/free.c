/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 11:24:29 by ayguillo          #+#    #+#             */
/*   Updated: 2019/05/29 11:26:19 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/op.h"

int	ft_freecom(char ***tab, int err, char *str)
{
	if (err == 0)
	{
		ft_printf("Command '%s' invalid\n", *tab[0]);
		ft_free_tab2d(tab);
		return (-1);
	}
	if (err == 1)
	{
		ft_free_tab2d(tab);
		ft_printf("%s is not a string\n", str);
		return (-1);
	}
	return (0);
}

int	ft_free(char ***tab, int err)
{
	if (err == 0)
	{
		ft_free_tab2d(tab);
		ft_putstr("Empty name\n");
		return (-1);
	}
	if (err == 1)
	{
		ft_free_tab2d(tab);
		ft_printf("Champion name too long (Max length %i)\n", PROG_NAME_LENGTH);
		return (-1);
	}
	if (err == 2)
	{
		ft_putstr("malloc error \n");
		ft_free_tab2d(tab);
		return (0);
	}
	return (0);
}
