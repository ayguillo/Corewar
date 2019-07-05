/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 11:40:25 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/05 12:03:04 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdlib.h>
#include "../includes/asm.h"

int				ft_retgnl(int fd, t_gnl *gnl, int i)
{
	int		ret;
	char	*trim;

	ft_strdel(&(gnl->line));
	ret = 0;
	while ((ret = ft_gnl(fd, &(gnl->line))) > 0)
	{
		gnl->nbline++;
		if (gnl->line)
		{
			trim = ft_strtrim(gnl->line);
			if ((i == 1 && trim[0] == '.') || i == 0)
			{
				ft_strdel(&trim);
				return (ret);
			}
			ft_strdel(&trim);
		}
		ft_strdel(&(gnl->line));
	}
	return (0);
}

short			ft_opc(int param1, int param2, int param3)
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

static char		*ft_charwtspaces(char *str)
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

int				ft_separator(char **str, int nb, char **line)
{
	int		i;
	char	*spaces;
	int		issep;
	int		ret;

	issep = 0;
	ret = 1;
	if (!(spaces = ft_charwtspaces(*str)))
		ret = (ft_free(NULL, 2, NULL, str));
	i = -1;
	while (spaces[++i] && ret != 0)
	{
		if (spaces[i] == SEPARATOR_CHAR)
		{
			nb = (issep == 1) ? nb : nb - 1;
			ret = (issep == 1) ? ft_syntax(str, 0, line, spaces[i]) : ret;
			issep = 1;
		}
		else if (spaces[i] != SEPARATOR_CHAR)
			issep = 0;
		if (nb < 0)
			ret = (ft_syntax(str, 1, line, 0));
	}
	ft_strdel(&spaces);
	return (nb != 0 ? ft_syntax(str, 1, line, 0) : ret);
}

unsigned long	ft_atui(const char *str)
{
	unsigned long	res;
	int				i;

	i = 0;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			return (0);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + ((str[i] - '0'));
		i++;
	}
	return (res);
}

/*
int		ft_itoo(unsigned char *str, char *str_nb, unsigned long long int size
		, int *index)
{
	unsigned long long int nb;
	unsigned long long int i;
	unsigned long long int div;

	i = size;
	div = 1;
	if (*index + (int)size >= CHAMP_MAX_SIZE)
		return (0);
	nb = (ft_atoll(str_nb) - 1) % 9223372036854775807;
	while (--i > 0)
		div *= 256;
	nb %= div * 256;
	while (i < size)
	{
		str[i] = (unsigned char)(nb / div);
		nb %= div;
		div /= 256;
		i++;
	}
	*index += (int)size;
	return (1);
}
*/
