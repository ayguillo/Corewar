/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_process_get_instruction.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 20:38:51 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/25 20:57:58 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "../libft/libft.h"

int		test_function()
{
	ft_putendl("SUCCESS");
	return (0);
}

int		(*get_instruction(int opcode))()
{
	if (opcode == 0x01)
		return (&test_function);
	return (NULL);
}

int		(*process_get_instruction(t_vm *vm, t_proc *process))()
{
	int pc;
	int opcode;

	pc = process->pc % MEM_SIZE;
	opcode = vm->mem[pc];
	return (get_instruction(opcode));
}

int main(void)
{
	t_vm	vm;
	t_proc	process;
	int		(*fptr)(void);

	ft_bzero(&vm, sizeof(vm));
	ft_bzero(&process, sizeof(process));
	vm.mem[0] = 1;
	fptr = process_get_instruction(&vm, &process);
	fptr();
	return (0);
}
