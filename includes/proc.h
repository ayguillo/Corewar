/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:08:26 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/02 17:27:46 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROC_H
# define PROC_H

# include <stdbool.h>
# include "../libft/libft.h"
# include "../libft/ft_printf.h"
# include "vm_structs.h"
# include "display.h"

# define T_SDIR 2
# define T_LDIR 4
# define ERROR -1
# define NO_ERROR 0
# define T_OPCODE 1
# define T_OCP 1
# define GLOBAL_DBG 0
# define VISU_ON 1

/*
** MAIN
*/

int	placeholder_init_data(t_vm *vm, t_proc *process);
void exec_op(unsigned char opcode, t_vm *vm, t_proc *process);
int	process_execute(t_vm *vm, t_proc *process);

/*
** DEBUG
*/

void tmp_print_mem(unsigned char *mem, unsigned int size);
void local_dbg(bool debug, const char *fmt_msg, ...);

/*
** INSTRUCTIONS
*/

void op_and(t_vm *vm, t_proc *process);
void op_jmpz(t_vm *vm, t_proc *process);
void op_live(t_vm *vm, t_proc *process);
void op_sti(t_vm *vm, t_proc *process);

/*
** INSTRUCTION TOOLS
*/

int	get_instruction_parameter(t_vm *vm, t_proc *proc, t_param *param);

/*
** READ FROM VM/PROCESS
*/

int	read_from_register(t_proc *proc, int id);
unsigned char read_byte_from_vm(t_vm *vm, int address);
int	read_from_vm(t_vm *vm, int address, int read_size);

/*
** WRITE TO VM/PROCESS
*/

void	write_to_register(t_proc *process, int register_id, int write);
void	write_byte_to_vm(t_vm *vm, int address, char byte);
void	write_to_vm(t_vm *vm, int address, int write, int write_size);

/*
** VM QUERY
*/

int	player_exist(t_vm *vm, int player_id);

/*
** VM SET
*/

void set_player_alive(t_vm *vm, t_proc *process, int player_id);

/*
** OCP TOOLS
*/

int		get_param_type_from_ocp(char ocp, int param_position);
void	set_params_from_ocp(t_param *param, char ocp, int nbr_of_params);

#endif
