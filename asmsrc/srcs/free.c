/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 13:32:57 by ayguillo          #+#    #+#             */
/*   Updated: 2019/08/02 13:35:42 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/op.h"
#include "../includes/asm.h"
#include "../libft/color.h"

int			ft_free(char ***tab, int err, t_gnl *gnl, char **str)
{
	int i;
	int	tot;
	int	cal;

	if (err == 0)
	{
		ft_strdel(str);
		ft_free_tab2d(tab);
		ft_dprintf(2, "Empty command at line %i\n%s%s\n", gnl->nbline,
				_RED_, gnl->line);
		i = 0;
		while (gnl->line[i] != '.')
			i++;
		ft_dprintf(2, "%s%*c%s\n", _GREEN_, ft_strclentab(gnl->line, 0,
					&gnl->line[i], 0),
				'^', _RESET_);
	}
	if (err == 1)
	{
		ft_strdel(str);
		ft_free_tab2d(tab);
		ft_dprintf(2, "Champion name too long (Max length %i)\n%sThe name \
has %i characters\n%s", PROG_NAME_LENGTH, _RED_, ft_strlen(gnl->line), _RESET_);
	}
	if (err == 2)
	{
		ft_strdel(str);
		ft_free_tab2d(tab);
		ft_putstr_fd("Malloc Error\n", 2);
	}
	if (err == 3)
	{
		ft_strdel(str);
		ft_free_tab2d(tab);
		ft_dprintf(2, "Comment too long (Max length %i)\n%sYour comment \
has %i characters\n%s", COMMENT_LENGTH, _RED_, ft_strlen(gnl->line), _RESET_);
	}
	if (err == 4)
	{
		ft_dprintf(2, "Champion too long. End of file at line %i\n",
				gnl->nbline);
	}
	if (err == 5)
	{
		i = -1;
		tot = 0;
		while (gnl->line[++i])
		{
			if (gnl->line[i] == '\t')
			{
				cal = 8 - (tot % 8);
				tot += cal;
			}
			else
				tot++;
			if (gnl->line[i] == '.')
				break ;
		}
		ft_dprintf(2, "comment is unexpected at line %i. Error at name.\
\n%s%s\n%s%*c%s\n",
				gnl->nbline, _RED_, gnl->line, _GREEN_, tot, '^', _RESET_);
		ft_strdel(str);
		ft_free_tab2d(tab);
	}
	ft_strdel(&(gnl->line));
	return (0);
}
