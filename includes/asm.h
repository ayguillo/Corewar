/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 17:41:10 by ayguillo          #+#    #+#             */
/*   Updated: 2019/05/29 13:52:51 by ayguillo         ###   ########.fr       */
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
int				ft_recupname(t_header *header, char *line, t_file file);
int				ft_recupcom(t_header *header, char *line, t_file file);
int				ft_freecom(char ***tab, int err, char *str);
int				ft_free(char ***tab, int err);

#endif
