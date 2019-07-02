/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:23:18 by vlambert          #+#    #+#             */
/*   Updated: 2019/07/02 16:55:46 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "../includes/vm_structs.h"
# include "../includes/op.h"
# include "../includes/errors.h"
# include "../includes/proc.h"
# include "../includes/display.h"

int					options(int ac, char *av[], t_vm *vm);
int					read_champ(char *champ, t_vm *vm);
int					create_arena(t_vm *vm);
int					game_cycle(t_vm *vm);
void				print_arena(t_vm *vm);

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
