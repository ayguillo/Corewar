/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freecom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 11:24:29 by ayguillo          #+#    #+#             */
/*   Updated: 2019/08/02 13:35:50 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/op.h"
#include "../includes/asm.h"
#include "../libft/color.h"

static void	ft_notstring(char ***tab, char *str, t_gnl *gnl)
{
	int		ret;
	int		i;
	int		j;
	int		tmpret;
	int		tmpi;

	ret = 0;
	i = 0;
	ft_dprintf(2, "%s is not a string, line %i\n%s%s%s\n", str, gnl->nbline,
			_RED_, gnl->line, _GREEN_);
	while (gnl->line[i] != (*tab)[0][0])
		ret = ft_passtab(gnl->line, &i, ret);
	j = -1;
	while (gnl->line[i++] == (*tab)[0][++j])
		ret++;
	while (gnl->line[i] == ' ' || gnl->line[i] == '\t')
		ret = ft_passtab(gnl->line, &i, ret);
	ret++;
	tmpret = ret;
	tmpi = i;
	if (gnl->line[i] == '\"')
		ft_dprintf(2, "%*c", ret++, ' ');
	else
		ft_dprintf(2, "%*c", ret, '^');
	while (gnl->line[i])
	{
		if (gnl->line[i] == '\t')
		{
			j = 8 - (ret % 8);
			ret += j;
			while (j-- > 0)
				ft_dprintf(2, "~");
		}
		else
		{
			ret++;
			ft_dprintf(2, "~");
		}
		i++;
	}
	if (gnl->line[tmpi] != '\"')
	{
		ft_dprintf(2, "\n%*c\n%s", tmpret, '\"', _RESET_);
	}
	else
	{
		ft_dprintf(2, "~");
		ft_dprintf(2, "%c\n%*c\n%s", '^', ret + 1, '\"', _RESET_);
	}
}

int			ft_freecom(char ***tab, int err, char *str, t_gnl *gnl)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	if (err == 0)
	{
		s = ft_strstr(gnl->line, str);
		ft_dprintf(2, "Command '%s' invalid at line %i\n", *tab[0],
				gnl->nbline);
		ft_dprintf(2, "%s%s\n%s", _RED_, gnl->line, _GREEN_);
		ft_strprintspaces(gnl->line);
		ft_dprintf(2, "%*c%s\n", ft_diffis(str, *tab[0]) + 1, '^', _RESET_);
		ft_free_tab2d(tab);
	}
	if (err == 1)
		ft_notstring(tab, str, gnl);
	if (err == 3)
	{
		ft_dprintf(2, "Syntax Error at line %i\n%s%s\n%s", gnl->nbline, _RED_,
				gnl->line, _GREEN_);
		j = 0;
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
		ft_dprintf(2, "%*c%s\n", ft_strclentab(gnl->line, '~', &(gnl->line[i]), 0), '^', _RESET_);
	}
	if (tab)
		ft_free_tab2d(tab);
	ft_strdel(&(gnl->line));
	return (0);
}