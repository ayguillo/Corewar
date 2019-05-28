/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 10:03:54 by vlambert          #+#    #+#             */
/*   Updated: 2019/03/20 18:30:50 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static int	double_line(char *buff)
{
	if (buff[0] == '\n')
		return (1);
	while (buff[0] && buff[1])
	{
		if (buff[0] == '\n' && buff[1] == '\n')
			return (1);
		buff++;
	}
	return (0);
}

char		*ft_read_all(int fd)
{
	char	*buff;
	char	*to_free;
	char	to_read[BUFF_SIZE + 1];
	int		ret;

	buff = NULL;
	while ((ret = read(fd, to_read, BUFF_SIZE)) > 0 && *to_read)
	{
		to_read[ret] = 0;
		if (buff == NULL)
			buff = ft_strdup(to_read);
		else
		{
			to_free = buff;
			buff = ft_strjoin(buff, to_read);
			ft_strdel(&to_free);
		}
		if (double_line(buff))
			return (buff);
	}
	if (ret < 0 || (ret != 0 && !(*to_read)))
		ft_strdel(&buff);
	return (buff);
}
