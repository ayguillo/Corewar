/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 17:41:10 by ayguillo          #+#    #+#             */
/*   Updated: 2019/06/03 14:58:52 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"

typedef struct	s_file
{
	int		fdopen;
	int		fdwrite;
	char	*name;
}				t_file;

int				printfile(t_header *header, t_file file);
int				ft_recupname(t_header *header, char **line, int *len);
int				ft_recupcom(t_header *header, char **line, int *len);
int				ft_freecom(char ***tab, int err, char *str, char **line);
int				ft_free(char ***tab, int err, char **line);

typedef struct		s_op
{
	char		*label;
	int			size;
	int			pos;
	struct s_op	*next;
}					t_op;

int				ft_inst(t_file file, int ret, char **line);

# define LIVE 0x01
# define LD 0x02
# define ST 0x03
# define ADD 0x04
# define SUB 0x05
# define AND 0x06
# define OR 0x07
# define XOR 0x08
# define ZJMP 0x09
# define LDI 0x0A
# define STI 0x0B
# define FORK 0x0C
# define LLD 0x0D
# define LLDI 0x0E
# define LFORK 0x0F
# define AFF 0x10

#endif
