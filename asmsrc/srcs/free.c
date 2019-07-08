/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 11:24:29 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/08 15:01:08 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/op.h"
#include "../includes/asm.h"
#include "../libft/color.h"

int	ft_freecom(char ***tab, int err, char *str, t_gnl *gnl)
{
	int		i;
	int		j;

	i = 0;
	if (err == 0)
	{
		ft_dprintf(2, "Command '%s' invalid at line %i\n", *tab[0],
				gnl->nbline);
		ft_dprintf(2, "%s%s\n%s", _RED_, gnl->line, _GREEN_);
		ft_strprintspaces(gnl->line);
		ft_dprintf(2, "%*c%s\n", ft_diffis(str, *tab[0]) + 1, '^', _RESET_);
		ft_free_tab2d(tab);
	}
	if (err == 1)
	{
		ft_dprintf(2, "%s is not a string, line %i\n%s%s\n", str, gnl->nbline,
				_RED_, gnl->line);
		while (gnl->line[i] == (*tab)[0][i])
		{
			ft_dprintf(2, "%c", ' ');
			i++;
		}
		while (gnl->line[i])
		{
			if (gnl->line[i] == '\t')
			{
				j = i;
				while (j % 7 != 0)
				{
					ft_dprintf(2, "%s%c", _GREEN_, '~');
					j++;
				}
			}
			ft_dprintf(2, "%s%c", _GREEN_, '~');
			i++;
		}
		ft_dprintf(2, "%c%s\n", '^', _RESET_);
		ft_free_tab2d(tab);
	}
	if (err == 3)
	{
		ft_dprintf(2, "Syntax Error at line %i\n%s%s\n%s", gnl->nbline, _RED_,
				gnl->line, _GREEN_);
		while (gnl->line[i++])
		{
			j = -1;
			if (gnl->line[i] != ' ' && gnl->line[i] != '\t')
			{
					while (LABEL_CHARS[++j])
					if (LABEL_CHARS[j] == gnl->line[i])
						break ;
				if (LABEL_CHARS[j] == '\0')
					break ;
			}
		}
		ft_dprintf(2, "%*c\n", ft_strclentab(gnl->line,
					gnl->line[i], '~'), '^', _RESET_);
	}
	ft_strdel(&(gnl->line));
	return (0);
}

int	ft_free(char ***tab, int err, t_gnl *gnl, char **str)
{
	if (err == 0)
	{
		ft_strdel(str);
		ft_free_tab2d(tab);
		ft_dprintf(2, "Empty command at line %i\n%s%s\n", gnl->nbline,
				_RED_, gnl->line);
		ft_dprintf(2, "%s%*c%s\n", _GREEN_, ft_strclentab(gnl->line, '.', 0),
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
		ft_dprintf(2, "Comment too long (Max length %i)\n%sYour comment\
has %i characters\n%s", COMMENT_LENGTH, _RED_, ft_strlen(gnl->line), _RESET_);
	}
	ft_strdel(&(gnl->line));
	return (0);
}
