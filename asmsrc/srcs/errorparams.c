/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorparams.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:08:58 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/10 16:06:16 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/libft.h"
#include "../libft/color.h"

int		ft_errorparams(t_gnl *gnl, int err, char *s, int occ)
{
	int		i;
	char	*str;

	if (err == 0)
	{
		str = ft_strstr(gnl->line, s);
		ft_dprintf(2, "Bad argument at line %i. Did you mean '%c%s' ?\n%s%s\n",
				gnl->nbline, DIRECT_CHAR, s, _RED_, gnl->line);
		ft_dprintf(2, "%s%*c%s\n", _GREEN_,
				ft_strclentab(gnl->line, 0, str, occ), '^', _RESET_);
	}
	if (err == 1)
	{
		str = ft_strstr(gnl->line, s);
		ft_dprintf(2, "Bad argument at line %i. Did you mean 'r%s' ?\n%s%s\n",
				gnl->nbline, s, _RED_, gnl->line);
		ft_dprintf(2, "%s%*c%s\n", _GREEN_,
				ft_strclentab(gnl->line, 0, str, occ), '^', _RESET_);
	}
	if (err == 2)
	{
		str = ft_strstr(gnl->line, s);
		ft_dprintf(2, "Wrong register at line %i. Min = 1 or Max = %i\n%s%s\n"
				, gnl->nbline, REG_NUMBER, _RED_, gnl->line);
		i = 0;
		while (s[i] && (s[i] < '0' || s[i] > '9'))
			i++;
		ft_dprintf(2, "%s%*c", _GREEN_, ft_strclentab(gnl->line, 0, str, occ),
				'^');
		while (s[i] && (s[++i] >= '0' && s[i] <= '9'))
			ft_dprintf(2, "~");
		ft_dprintf(2, "\n%s", _RESET_);
	}
	ft_strdel(&(gnl->line));
	return (0);
}
