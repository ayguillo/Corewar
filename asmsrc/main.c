/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 12:59:06 by ayguillo          #+#    #+#             */
/*   Updated: 2019/06/05 11:01:50 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "../includes/asm.h"

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
		return (NULL);
	ft_strncpy(rname, name, chr - name);
	if (!(ext = ft_strdup(".cor")))
		return (NULL);
	join = ft_strjoinfree(rname, ext);
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

int			start(int ac, char **av, t_file *file)
{
	if (ac != 2)
	{
		ft_printf("Arguments invalid\n");
		return (0);
	}
	if ((file->fdopen = open(av[1], O_RDONLY)) == -1)
	{
		ft_printf("Open() failed\n");
		return (0);
	}
	if (!(file->name = ft_recupfile(av[1])))
	{
		ft_strdel(&(file->name));
		ft_printf("File is not .s\n");
		return (0);
	}
	return (1);
}

int			main(int ac, char **av)
{
	t_file			file;
	t_header		header;

	ft_bzero(&file, sizeof(file));
	ft_bzero(&header, sizeof(header));
	if (!(start(ac, av, &file)))
		return (-1);
	if (!(printfile(&header, file)))
	{
		ft_strdel(&(file.name));
		return (-1);
	}
	if (((file.fdwrite = createfile(file.name)) == -1))
	{
		ft_strdel(&(file.name));
		ft_printf("Open() failed\n");
		return (-1);
	}
	write(file.fdwrite, &header, sizeof(t_header));
	if ((close(file.fdopen)) == -1 || (close(file.fdwrite) == -1))
	{
		ft_strdel(&(file.name));
		ft_printf("Close() failed\n");
		return (-1);
	}
	ft_strdel(&(file.name));
	return (0);
}
