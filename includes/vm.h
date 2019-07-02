/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:23:18 by vlambert          #+#    #+#             */
/*   Updated: 2019/07/02 08:49:10 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "../includes/op.h"
# include "../includes/errors.h"

typedef struct		s_proc
{
	struct s_proc	*next;
	unsigned int	pc;
	unsigned int	number;
	int				period_lives;
	int				waiting;
	int				carry;
	int				regs[REG_NUMBER];
	int				player;
	int				dir_size;
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
	int				cycles_limit;
	int				period_cycles;
	int				cycle_to_die;
	int				checks;
	int				period_lives;
	int				options;
	int				players_nbr;
	char			err[ERR_TYPE_NBR][ERR_MSG_SIZE];
	//t_display		display;
}					t_vm;

int					options(int ac, char *av[], t_vm *vm);
int					read_champ(char *champ, t_vm *vm);
int					create_arena(t_vm *vm);
int					game_cycle(t_vm *vm);

/*
**	Set end to 1 to kill all the processes even if they made a life
**	Set end to 0 to kill only thee unactives ones
*/
void				kill_unactive_processes(t_vm *vm, int end);

/*
**	The arg player correspond to the index in vm->players of the player
**	The arg src correspond to the source process in case of a fork or null
**	in other cases
*/
int					add_process(t_vm *vm, int player, unsigned int pc,
						t_proc *src);

/*
**  Set errors messages and error code to 0
**  Add a new error message by adding :
**  	ft_strcpy(vm->err[ERR_XXXXXX], "Your message"); 
**	in errors.c following function.
**	Your message must respect ERR_MSG_SIZE size and refer to errors.h
*/
void    init_err(t_vm *vm, int *err);

#endif
