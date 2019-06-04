/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:11:17 by ayguillo          #+#    #+#             */
/*   Updated: 2019/06/03 16:28:32 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/asm.h"

short	ft_opc(int param1, int param2, int param3)
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

int		ft_recupinst(char **line, t_op *op)
{
	char	*trim;
	char	**split;
	int		i;

	op = NULL;
	i = -1;
	if (!(trim = ft_strtrim(*line)))
		return (ft_free(NULL, 2, line));
	while (trim[++i])
		if (trim[i] == COMMENT_CHAR)
			trim[i] = '\0';
	if (!(split = ft_strsplit(trim, ',')))
		return (ft_free(NULL, 2, line));
	ft_printf("split = %s\n", split[0]);
	return (0);
}

int		ft_inst(t_file file, int ret, char **line)
{
	t_op	*op;

	op = NULL;
	while (ret > 0)
	{
		ft_strdel(line);
		ret = ft_gnl(file.fdopen, line);
		if (*line[0] != COMMENT_CHAR)
			break ;
	}
	if (!(line))
		return (ft_freecom(NULL, -1, NULL, line));
	while (ret > 0)
	{
		if (!(ret = ft_recupinst(line, op)))
			return (0);
		ft_strdel(line);
	}
	return (1);
}
