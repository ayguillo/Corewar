/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorparams.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:08:58 by ayguillo          #+#    #+#             */
/*   Updated: 2019/08/01 17:43:31 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/libft.h"
#include "../libft/color.h"

static void	ft_wrongregister(t_asm *tasm, char *s, int occ)
{
	char	*str;
	int		i;

	str = ft_strstr(tasm->gnl.line, s);
	i = 0;
	ft_dprintf(2, "Wrong register at line %i. Min = 1 or Max = %i\n%s%s\n"
			, tasm->gnl.nbline, REG_NUMBER, _RED_, tasm->gnl.line);
	i = 0;
	while (s[i] && (s[i] < '0' || s[i] > '9'))
		i++;
	ft_dprintf(2, "%s%*c", _GREEN_, ft_strclentab(tasm->gnl.line, 0, str,
				occ),
			'^');
	while (s[i] && (s[++i] >= '0' && s[i] <= '9'))
		ft_dprintf(2, "~");
	ft_dprintf(2, "\n%s", _RESET_);
}

static void	ft_badarg(t_asm *tasm, char *s, int occ)
{
	char	*str;

	str = ft_strstr(tasm->gnl.line, s);
	ft_dprintf(2, "Bad argument at line %i. Did you mean 'r%s' ?\n%s%s\n",
			tasm->gnl.nbline, s, _RED_, tasm->gnl.line);
	ft_dprintf(2, "%s%*c\n", _GREEN_,
			ft_strclentab(tasm->gnl.line, 0, str, occ) - 1, '^');
	ft_dprintf(2, "%*c%s\n",
			ft_strclentab(tasm->gnl.line, 0, str, occ) - 1, 'r', _RESET_);
}

int			ft_errorparams(t_asm *tasm, char *s)
{
	int		i;
	char	*str;
	int		occ;

	occ = tasm->n_param - 1;
	if (tasm->error == 4)
	{
		str = ft_strstr(tasm->gnl.line, s);
		ft_dprintf(2, "Bad argument at line %i. Did you mean '%c%s' ?\n%s%s\n",
				tasm->gnl.nbline, DIRECT_CHAR, s, _RED_, tasm->gnl.line);
		i = 0;
		ft_dprintf(2, "%s%*c\n", _GREEN_,
				ft_strclentab(tasm->gnl.line, 0, str, occ) - 1, '^');
		ft_dprintf(2, "%*c", ft_strclentab(tasm->gnl.line, 0, str, occ) - 1
				, '%');
		ft_dprintf(2, "\n%s", _RESET_);
	}
	if (tasm->error == 1)
		ft_badarg(tasm, s, occ);
	if (tasm->error == 2)
		ft_wrongregister(tasm, s, occ);
	ft_strdel(&(tasm->gnl.line));
	return (0);
}
