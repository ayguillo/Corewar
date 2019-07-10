/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxerror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 14:56:44 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/10 16:55:40 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../libft/color.h"
#include "../includes/asm.h"

static void	ft_wsep(t_gnl *gnl, char c, int nparam)
{
	int		i;

	ft_dprintf(2, "Syntax Error. Wrong separator at line %i%s\n%s\n",
			gnl->nbline, _RED_, gnl->line);
	i = 0;
	while (gnl->line[i] && nparam)
	{
		if (gnl->line[i] == SEPARATOR_CHAR)
			nparam--;
		++i;
	}
	while (gnl->line[i] && gnl->line[i] == c)
		i++;
	ft_dprintf(2, "%s%*c%s\n", _GREEN_,
			ft_strclentab(gnl->line, 0, &gnl->line[i], nparam), '^', _RESET_);

}

static void	ft_wnbr(t_gnl *gnl)
{
	int		i;
	int		j;

	ft_dprintf(2, "Syntax Error. Wrong number of separator at line\
			%i\n%s%s\n", gnl->nbline, _RED_, gnl->line);
	i = 0;
	while (gnl->line[i] && gnl->line[i++] != COMMENT_CHAR)
	{
		if (gnl->line[i] == SEPARATOR_CHAR)
			j = i;
		if (gnl->line[i] == '\t' || gnl->line[i] == ' ')
			ft_dprintf(2, "%c", gnl->line[i]);
	}
	ft_dprintf(2, "%s%*c%s\n", _GREEN_, j, '^', _RESET_);
}

static void	ft_uinst(t_gnl *gnl, int nparam)
{
	int	i;
	int	j;

	ft_dprintf(2, "Unknow instruction at line %i\n%s%s\n", gnl->nbline,
			_RED_, gnl->line);
	i = 0;
	while (gnl->line[i] && (gnl->line[i] == '\t' || gnl->line[i] == 32))
		++i;
	j = ft_strclentab(gnl->line, 0, &gnl->line[i], nparam);
	ft_dprintf(2, "%s%*c", _GREEN_, j, '^');
	while (gnl->line[++i] && gnl->line[i] != '\t' && gnl->line[i] != 32)
		ft_dprintf(2, "%c", '~');
	ft_dprintf(2, "%s\n", _RESET_);
}

static void	ft_wchar(t_gnl *gnl, char c, int nparam)
{
	int	i;

	ft_dprintf(2, "Syntax Error. Wrong character at line %i%s\n%s\n",
			gnl->nbline, _RED_, gnl->line);
	i = 0;
	while (gnl->line[i] && nparam)
	{
		if (gnl->line[i] == SEPARATOR_CHAR)
			nparam--;
		i++;
	}
	while (gnl->line[i] && gnl->line[i] != c)
		i++;
	ft_dprintf(2, "%s%*c%s\n", _GREEN_, ft_strclentab(gnl->line, 0,
				&gnl->line[i], nparam), '^', _RESET_);
}

int			ft_syntax(char **str, int err, t_gnl *gnl, char c, int nparam)
{
	if (err == 0)
		ft_wsep(gnl, c, nparam);
	if (err == 1)
		ft_wnbr(gnl);
	if (err == 2)
		ft_uinst(gnl, nparam);
	if (err == 3)
		ft_wchar(gnl, c, nparam);
	ft_strdel(str);
	ft_strdel(&(gnl->line));
	return (0);
}
