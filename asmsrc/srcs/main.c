/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 12:59:06 by ayguillo          #+#    #+#             */
/*   Updated: 2019/08/05 17:37:32 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../libft/color.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "../includes/asm.h"

int			ft_closeall(t_asm tasm)
{
	if (tasm.file.fdopen)
	{
		if ((close(tasm.file.fdopen)) == -1)
		{
			ft_dprintf(2, "Close() failed\n");
			return (-1);
		}
	}
	if (tasm.file.fdwrite)
	{
		if ((close(tasm.file.fdwrite)) == -1)
		{
			ft_dprintf(2, "Close() failed\n");
			return (-1);
		}
	}
	return (1);
}

char		*ft_recupfile(char *name)
{
	char	*chr;
	char	*rname;
	char	*join;
	char	*ext;

	rname = NULL;
	ext = NULL;
	chr = NULL;
	join = NULL;
	chr = ft_strrchr(name, '.');
	if (!chr)
		return (NULL);
	if (ft_strcmp(chr, ".s"))
		return (NULL);
	if (!(rname = (char*)malloc(sizeof(char) * (chr - name + 1))))
	{
		ft_free(NULL, 2, NULL, NULL);
		return (NULL);
	}
	ft_strncpy(rname, name, chr - name);
	if (!(ext = ft_strdup(".cor")))
	{
		ft_free(NULL, 2, NULL, NULL);
		return (NULL);
	}
	if (!(join = ft_strjoinfree(rname, ext)))
	{
		ft_free(NULL, 2, NULL, NULL);
		return (NULL);
	}
	return (join);
}

int			createfile(char *name)
{
	int		fd;

	if ((fd = open(name, O_CREAT | O_TRUNC | O_RDWR, 00755)) == -1)
		return (-1);
	if (fd != -1)
	{
		if ((fd = open(name, O_RDWR)) == -1)
			return (-1);
	}
	return (fd);
}

int			start(/*int ac, */char **av, t_file *file, int i)
{
/*	if (ac != 2)
	{
		ft_dprintf(2, "Arguments invalid\n");
		return (0);
	}*/
	if ((file->fdopen = open(av[i], O_RDONLY)) == -1)
	{
		ft_dprintf(2, "Open() failed\n");
		return (0);
	}
	if (!(file->name = ft_recupfile(av[i])))
	{
		ft_strdel(&(file->name));
		ft_dprintf(2, "File is not .s\n");
		return (0);
	}
	return (1);
}

void		ft_dellstop(t_asm *tasm)
{
	t_op	*tmp1;
	t_op	*tmp2;
	int		i;

	tmp1 = tasm->op;
	ft_strdel(&(tasm->gnl.line));
	while (tmp1)
	{
		i = -1;
		tmp2 = tmp1->next;
		while (++i < 3)
			ft_strdel(&tmp1->searchlabel[i]);
		ft_strdel(&tmp1->label);
		free(tmp1);
		tmp1 = NULL;
		tmp1 = tmp2;
	}
}

int			multifile(char **av, int i)
{
	t_header	header;
	t_asm		tasm;

	ft_bzero(&header, sizeof(header));
	ft_bzero(&tasm, sizeof(tasm));
	ft_bzero(&tasm, sizeof(tasm.op));
	ft_printf("Compiling %s . . .\n", av[i]);
	if (!(start(/*ac, */av, &(tasm.file), i)))
		return (-1);
	if (!(printfile(&header, &tasm)))
	{
		while ((ft_gnl(tasm.file.fdopen, &(tasm.gnl.line))) > 0)
			ft_strdel(&(tasm.gnl.line));
		ft_closeall(tasm);
		ft_strdel(&(tasm.file.name));
		ft_dellstop(&tasm);
		return (-1);
	}
	if (((tasm.file.fdwrite = createfile(tasm.file.name)) == -1))
	{
		while ((ft_gnl(tasm.file.fdopen, &(tasm.gnl.line))) > 0)
			ft_strdel(&(tasm.gnl.line));
		ft_closeall(tasm);
		ft_strdel(&(tasm.file.name));
		ft_dellstop(&tasm);
		ft_dprintf(2, "Open() failed\n");
		return (-1);
	}
	if (ft_searchlabel(&tasm, 1))
	{
		write(tasm.file.fdwrite, &header, sizeof(t_header));
		write_code(&(tasm.file), tasm.op);
		ft_printf("%sWriting output program to %s%s\n",
				_GREEN_, tasm.file.name, _RESET_);
	}
	while ((ft_gnl(tasm.file.fdopen, &(tasm.gnl.line))) > 0)
		ft_strdel(&(tasm.gnl.line));
//	ft_closeall(tasm);
	ft_strdel(&(tasm.file.name));
	ft_dellstop(&tasm);
	return (1);
}


int			main(int ac, char **av)
{
/*	t_header		header;
	t_asm			tasm;*/
	int				i;

	i = 0;
	while (++i < ac)
	{
		multifile(av, i);
	/*	ft_printf("Compiling %s . . .\n", av[i]);
		ft_bzero(&header, sizeof(header));
		ft_bzero(&tasm, sizeof(tasm));
		ft_bzero(&tasm, sizeof(tasm.op));
		if (!(start(ac, av, &(tasm.file))))
		{
			ft_closeall(tasm);
			return (-1);
		}
		if (!(printfile(&header, &tasm)))
		{
			ft_closeall(tasm);
			ft_strdel(&(tasm.file.name));
			ft_dellstop(&tasm);
			return (-1);
		}
		if (((tasm.file.fdwrite = createfile(tasm.file.name)) == -1))
		{
			ft_closeall(tasm);
			ft_strdel(&(tasm.file.name));
			ft_dellstop(&tasm);
			ft_dprintf(2, "Open() failed\n");
			return (-1);
		}
		if (ft_searchlabel(&tasm, 1))
		{
			write(tasm.file.fdwrite, &header, sizeof(t_header));
			write_code(&(tasm.file), tasm.op);
			ft_printf("%sWriting output program to %s%s\n",
					_GREEN_, tasm.file.name, _RESET_);
		}
		ft_closeall(tasm);
		ft_dellstop(&tasm);
		ft_strdel(&(tasm.file.name));*/
	}
	return (0);
}
