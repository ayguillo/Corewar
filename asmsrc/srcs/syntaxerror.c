/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxerror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 14:56:44 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/16 11:21:30 by ayguillo         ###   ########.fr       */
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
	int		tot;

	ft_dprintf(2, "Syntax Error. Wrong number of separator at line %i\n%s%s\n",
			gnl->nbline, _RED_, gnl->line);
	i = 0;
	tot = 0;
	while (gnl->line[i] && gnl->line[i++] != COMMENT_CHAR)
	{
		if (gnl->line[i] == SEPARATOR_CHAR)
			j = i;
		if (gnl->line[i] == '\t')
			tot += 8 - (tot % 8);
		else
			tot++;
	}
	ft_dprintf(2, "%s%*c%s\n", _GREEN_, tot, '^', _RESET_);
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
	while (gnl->line[++i] && gnl->line[i] != '\t' && gnl->line[i] != 32 &&
			gnl->line[i] != SEPARATOR_CHAR)
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
	ft_dprintf(2, "%s%*c", _GREEN_, ft_strclentab(gnl->line, 0,
				&gnl->line[i], nparam), '^');
	while (gnl->line[++i] && gnl->line[i] != ' ' && gnl->line[i] != '\t' &&
			gnl->line[i] != SEPARATOR_CHAR)
		ft_dprintf(2, "~");
	ft_dprintf(2, "\n%s", _RESET_);
}

int			ft_syntax(char **str, t_asm *tasm, char c)
{
	tasm->n_param--;
	if (tasm->error == 0)
		ft_wsep(&(tasm->gnl), c, tasm->n_param);
	if (tasm->error == 1)
		ft_wnbr(&(tasm->gnl));
	if (tasm->error == 2)
		ft_uinst(&(tasm->gnl), tasm->n_param);
	if (tasm->error == 3)
		ft_wchar(&(tasm->gnl), c, tasm->n_param);
	ft_strdel(str);
	ft_strdel(&(tasm->gnl.line));
	tasm->error = 5;
	return (0);
}
