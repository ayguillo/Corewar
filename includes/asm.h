/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 17:41:10 by ayguillo          #+#    #+#             */
/*   Updated: 2019/06/24 14:22:06 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"

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

typedef struct	s_file
{
	int		fdopen;
	int		fdwrite;
	char	*name;
}				t_file;

/*
** HEADER
*/

int				printfile(t_header *header, t_file file);
int				ft_recupname(t_header *header, char **line, int *len);
int				ft_recupcom(t_header *header, char **line, int *len);

/*
 ** ERROR
*/

int				ft_freecom(char ***tab, int err, char *str, char **line);
int				ft_free(char ***tab, int err, char **line, char **str);
int				ft_syntax(char **tab, int err, char **line, char c);

/*
** TOOLS
*/

int				ft_retgnl(int fd, char **line);
unsigned int	ft_reversebyte(unsigned int byte);
short			ft_opc(int param1, int param2, int param3);
int				ft_separator(char **str, int nb, char **line);

/*
** INSTRUCTIONS & LABEL
*/

typedef struct	s_op
{
	char		*label;
	int			size;
	int			addr;
	int			nbarg;
	int			inst;
	int			code1;
	int			code2;
	int			code3;
	int			param1;
	int			param2;
	int			param3;
	struct s_op	*next;
}				t_op;

int				ft_readinst(t_file file, int ret, char **line);
int				ft_readn(t_file file, char **line, int *ret);
int				ft_label(char *trim, char **line, t_op *new);
int				ft_instructions(char **trim, char **line, t_op **op);
void			ft_paramlive(char **split, t_op *op);
void			ft_fillparam1(t_op *op, int size, int code,
		unsigned int param1);
int				ft_paramlabel(t_op *op, char *label);

#endif
