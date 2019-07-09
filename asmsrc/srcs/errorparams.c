/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorparams.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:08:58 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/09 10:57:49 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/libft.h"
#include "../libft/color.h"

int		ft_errorparams(t_gnl *gnl, int err, char c, char *s)
{
	int		i;

	if (err == 0)
	{
		ft_dprintf(2, "Bad argument at line %i. Did you mean '%c%s' ?\n%s%s\n",
				gnl->nbline, DIRECT_CHAR, s, _RED_, gnl->line);
		ft_dprintf(2, "%s%*c%s\n", _GREEN_, ft_strclentab(gnl->line, c, 0), '^',
				_RESET_);
	}
	if (err == 1)
	{
		ft_dprintf(2, "Bad argument at line %i. Did you mean 'r%s' ?\n%s%s\n",
				gnl->nbline, s, _RED_, gnl->line);
		ft_dprintf(2, "%s%*c%s\n", _GREEN_, ft_strclentab(gnl->line, c, 0), '^',
				_RESET_);
	}
	if (err == 2)
	{
		ft_dprintf(2, "Wrong register at line %i. Min = 1 or Max = %i\n%s%s\n"
				, gnl->nbline, REG_NUMBER, _RED_, gnl->line);
		i = 0;
		while (s[i] && (s[i] < '0' || s[i] > '9'))
			i++;
		ft_dprintf(2, "%s%*c", _GREEN_, ft_strclentab(gnl->line, s[i], 0),
				'^');
		while (s[i] && (s[++i] >= '0' && s[i] <= '9'))
			ft_dprintf(2, "~");
		ft_dprintf(2, "\n%s", _RESET_);
	}
	ft_strdel(&(gnl->line));
	return (0);
}
