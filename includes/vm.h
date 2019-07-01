/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:23:18 by vlambert          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/07/01 12:39:30 by vlambert         ###   ########.fr       */
=======
/*   Updated: 2019/07/01 12:13:50 by vlambert         ###   ########.fr       */
>>>>>>> 2ced78e9e631a595022b98c3f38c487036ff1ea6
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
	int				period_lives;
	unsigned int	pc;
	int				waiting;
	int				carry;
	int				regs[REG_NUMBER];
	int				player;
}					t_proc;

typedef struct		s_player
{
	int				number;
	int				period_lives;
	int				last_p_lives;
	int				alive_proc;
	unsigned int	size;
	char			name[PROG_NAME_LENGTH + 4];
	char			comment[COMMENT_LENGTH + 4];
	unsigned char	code[CHAMP_MAX_SIZE + 1];
}					t_player;

typedef struct		s_vm
{
	unsigned char	mem[MEM_SIZE];
	t_player		players[MAX_PLAYERS];
	t_proc			*proc;
	int				last_player_alive;
	int				cycles;
	int				period_cycles;
	int				cycle_to_die;
	int				cycles_limit;
<<<<<<< HEAD
=======
	int				checks;
	int				period_lives;
>>>>>>> 2ced78e9e631a595022b98c3f38c487036ff1ea6
	int				options;
	int				players_nbr;
	char			err[ERR_TYPE_NBR][ERR_MSG_SIZE];
}					t_vm;

int					options(int ac, char *av[], t_vm *vm);
int					read_champ(char *champ, t_vm *vm);
int					create_arena(t_vm *vm);
void				kill_unactive_processes(t_player *player, int end);
int					add_process(t_vm *vm, t_player *player, unsigned int pc);

/*
**  Set errors messages and error code to 0
**  Add a new error message by adding :
**  	ft_strcpy(vm->err[ERR_XXXXXX], "Your message"); 
**	in errors.c following function.
**	Your message must respect ERR_MSG_SIZE size and refer to errors.h
*/
void    init_err(t_vm *vm, int *err);

#endif
