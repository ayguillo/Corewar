/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorparams.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:08:58 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/08 15:56:20 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/libft.h"
#include "../libft/color.h"

int		ft_errorparams(t_gnl *gnl, int err, char c)
{
	char r = c;
	r = c;
	if (err == 0)
	{
		ft_dprintf(2, "Bad argument at line %i\n%s%s\n", gnl->nbline, _RED_,
				gnl->line);
		ft_dprintf(2, "%s%*c%s\n", _GREEN_, ft_strclentab(gnl->line, c, 0), '^',
				_RESET_);
	}
	ft_strdel(&(gnl->line));
	return (0);
}
