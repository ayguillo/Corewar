/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 11:40:25 by ayguillo          #+#    #+#             */
/*   Updated: 2019/06/17 15:49:51 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdlib.h>
#include "../includes/asm.h"

int				ft_retgnl(int fd, char **line)
{
	int		ret;

	ft_strdel(line);
	while ((ret = ft_gnl(fd, line)) > 0)
		if (*line)
			return (ret);
	return (ret);
}

unsigned int	ft_reversebyte(unsigned int byte)
{
	unsigned int	revbyte;
	int				i;

	i = 3;
	while (i >= 0)
	{
		((char*)(&revbyte))[i] = ((char*)(&byte))[0];
		byte = byte >> 8;
		i--;
	}
	return (revbyte);
}

short		ft_opc(int param1, int param2, int param3)
{
	short i;

	i = 0;
	i += param1;
	i = i << 2;
	i += param2;
	i = i << 2;
	i += param3;
	i = i << 2;
	return (i);
}

static char	*ft_charwtspaces(char *str)
{
	int		i;
	int		len;
	char	*news;

	i = -1;
	len = 0;
	while (str[++i])
		if ((str[i] < 9 || str[i] > 13) && str[i] != 32)
			len++;
	if (!(news = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	news[len--] = '\0';
	while (--i >= 0)
		if ((str[i] < 9 || str[i] > 13) && str[i] != 32)
		{
			news[len--] = str[i];
		}
	return (news);
}

int			ft_separator(char **str, int nb, char **line)
{
	int		i;
	char	*spaces;
	int		issep;
	int		n;
	int		ret;

	issep = 0;
	n = nb;
	ret = 1;
	if (!(spaces = ft_charwtspaces(*str)))
		ret = (ft_free(NULL, 2, NULL, str));
	i = -1;
	while (spaces[++i])
	{
		if (ret == 0)
			break ;
		if (spaces[i] == SEPARATOR_CHAR && issep == 0)
		{
			nb--;
			issep = 1;
		}
		else if (spaces[i] == SEPARATOR_CHAR && issep == 1)
			ret = (ft_syntax(str, 0, line, spaces[i]));
		else if (spaces[i] != SEPARATOR_CHAR)
			issep = 0;
		if (nb < 0)
			ret = (ft_syntax(str, 1, line, 0));
	}
	ft_strdel(&spaces);
	if (nb != 0)
		return (ft_syntax(str, 1, line, 0));
	return (ret);
}
