/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 17:41:10 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/09 12:26:36 by ayguillo         ###   ########.fr       */
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

# define COM 1
# define NAME 2

typedef struct	s_file
{
	int		fdopen;
	int		fdwrite;
	char	*name;
}				t_file;

typedef struct	s_gnl
{
	int		nbline;
	char	*line;
}				t_gnl;

typedef struct	s_op
{
	char			*label;
	char			*searchlabel;
	int				size;
	int				addr;
	int				nbarg;
	int				inst;
	int				code1;
	int				code2;
	int				code3;
	unsigned int	param1;
	unsigned int	param2;
	unsigned int	param3;
	struct s_op		*next;
}				t_op;

/*
** HEADER
*/

int				printfile(t_header *header, t_file file, t_op **op);
int				ft_recup(t_header *header, t_gnl *gnl, int *len, int type);

/*
 ** ERROR
*/

int				ft_freecom(char ***tab, int err, char *str, t_gnl *gnl);
int				ft_free(char ***tab, int err, t_gnl *gnl, char **str);
int				ft_syntax(char **tab, int err, t_gnl *gnl, char c);
int				ft_errorparams(t_gnl *gnl, int err, char c, char *s);

/*
** TOOLS
*/

int				ft_retgnl(int fd, t_gnl *gnl, int i);
short			ft_opc(int param1, int param2, int param3);
int				ft_separator(char **str, int nb, t_gnl *gnl);
unsigned long	ft_atui(const char *str);
int				ft_diffis(const char *s1, const char *s2);
int				ft_strclentab(const char *s1, char c, char print);
void			ft_strprintspaces(const char *s1);
char			*ft_charwtspaces(char *str);

/*
** INSTRUCTIONS & LABEL
*/

void			ft_filld(char **split, int nparam, t_op *op, int size);
void			ft_filli(char **split, int nparam, t_op *op);
void			ft_fillrg(char **split, int nparam, t_op *op);
void			ft_fillinstop(char *inst, t_op *op);
void			ft_fillinstop(char *inst, t_op *op);
int				ft_idd(char **split, t_op *op, int size, int nparam);
int				ft_rgidd(char **split, t_op *op, int size, int nparam);
int				ft_rgid(char **split, t_op *op, int param);

int				ft_readinst(t_file file, t_gnl *gnl, t_op **op);
int				ft_readn(t_file file, char **line, int *ret);
int				ft_instructions(char **trim, t_gnl *gnl, t_op **op);

int				ft_paramd(char **split, t_op *op, int size, t_gnl *gnl);
int				ft_paramrg(char **split, t_op *op, t_gnl *gnl);
int				ft_paramld(char **split, t_op *op, t_gnl *gnl);
int				ft_paramst(char **split, t_op *op, t_gnl *gnl);
int				ft_param3rg(char **split, t_op *op, t_gnl *gnl);
void			ft_paramldi(char **split, t_op *op);
void			ft_paramsti(char **split, t_op *op);
void			ft_paramcomp(char **split, t_op *op);

void			ft_fillparam1(t_op *op, int size, int code,
		unsigned int param1);
void			ft_fillparam2(t_op *op, int size, int code,
		unsigned int param2);
void			ft_fillparam3(t_op *op, int size, int code,
		unsigned int param3);


unsigned int	ft_filllabel(t_op *op, char **split, int nparam);

#endif
