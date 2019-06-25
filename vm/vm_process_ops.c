/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_process_ops.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 20:38:51 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/25 23:10:46 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../libft/ft_printf.h"
#include "vm.h"

int		player_exist(t_vm *vm, int player_id)
{
	if (player_id <= vm->players_nbr/* && vm->players[player_id] != 0*/)
		return (1);
	return (0);
}

void	set_player_alive(t_vm *vm, int player_id)
{
	(void)vm;
	ft_printf("Player %u is alive\n", player_id);
	/* Set vm->player[player_id] as 'alive' */
}

void	op_live(t_vm *vm, t_proc *process)
{
	int player_id;
	int pc;

	pc = process->pc % MEM_SIZE;
	player_id = *(unsigned int*)&vm->mem[pc + 1];
	if (player_exist(vm, player_id))
		set_player_alive(vm, player_id);
	/* Set up global pc and live settings */
}

void	(*g_op_set[2])(t_vm*, t_proc*) =
{
	NULL,
	&op_live,
};

void	exec_op(unsigned char opcode, t_vm *vm, t_proc *process)
{
	if (opcode >= 0 && opcode <= 1)
		g_op_set[opcode](vm, process);
}

int		process_execute(t_vm *vm, t_proc *process)
{
	unsigned int	pc;
	unsigned char	opcode;

	pc = process->pc % MEM_SIZE;
	opcode = vm->mem[pc];
	exec_op(opcode, vm, process);
	return (0);
}

int main(void)
{
	t_vm	vm;
	t_proc	process;

	ft_bzero(&vm, sizeof(vm));
	ft_bzero(&process, sizeof(process));
	vm.mem[0] = 1;

	process_execute(&vm, &process);
	return (0);
}
