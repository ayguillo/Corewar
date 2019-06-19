/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:23:18 by vlambert          #+#    #+#             */
/*   Updated: 2019/06/19 12:00:52 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "../includes/op.h"
# include "../includes/errors.h"

typedef struct		s_proc
{
	struct s_proc	*next;
	int				number;
	int				lives;
	int				last_live;
	int				alive;
	int				carry;
	int				pc;
	int				waiting;
}					t_proc;

typedef struct		s_player
{
	int				number;
	int				period_lives;
	int				last_p_lives;
	int				last_live;
	int				size;
	char			name[PROG_NAME_LENGTH];
	char			comment[COMMENT_LENGTH];
	char			code[CHAMP_MAX_SIZE + 1];
	t_proc			*proc;
}					t_player;

typedef struct		s_vm
{
	unsigned char	mem[MEM_SIZE];
	t_player		players[MAX_PLAYERS];
	int				player_turn;
	int				cycles;
	int				cycle_to_die;
	int				cycles_limit;
	int				process;
	int				options;
	int				players_nbr;
	char			err[10][ERR_MSG_SIZE];
}					t_vm;

int					options(int ac, char *av[], t_vm *vm);

#endif
