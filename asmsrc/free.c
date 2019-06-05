/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 11:24:29 by ayguillo          #+#    #+#             */
/*   Updated: 2019/06/05 17:24:19 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/op.h"

int	ft_freecom(char ***tab, int err, char *str, char **line)
{
	ft_strdel(line);
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
	if (err == 3)
	{
		ft_printf("'%s' syntax Error\n", str);
		return (0);
	}
	return (0);
}

int	ft_syntax(char **str, int err, char **line, char c)
{
	if (err == 0)
	{
		ft_strdel(str);
		ft_strdel(line);
		ft_printf("'%c' Syntax Error, Bad separator\n", c);
		return (0);
	}
	return (0);
}

int	ft_free(char ***tab, int err, char **line, char **str)
{
	ft_strdel(line);
	if (err == 0)
	{
		ft_strdel(str);
		ft_free_tab2d(tab);
		ft_putstr("Empty name\n");
		return (-1);
	}
	if (err == 1)
	{
		ft_strdel(str);
		ft_free_tab2d(tab);
		ft_printf("Champion name too long (Max length %i)\n", PROG_NAME_LENGTH);
		return (-1);
	}
	if (err == 2)
	{
		ft_strdel(str);
		ft_free_tab2d(tab);
		ft_putstr("Malloc error \n");
		return (0);
	}
	if (err == 3)
	{

	}
	return (0);
}
