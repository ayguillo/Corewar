/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_vm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 17:32:33 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/01 20:25:16 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/proc.h"

void	write_byte_to_vm(t_vm *vm, int address, char byte)
{
	int real_address;

	real_address = (address % MEM_SIZE);
	vm->mem[real_address] = byte;
}

void	write_to_vm(t_vm *vm, int address, int write, int write_size)
{
	int i;

	i = 0;
	while (i < write_size) /* WHAT IF WRITE_SIZE > 4 ? */
	{
		write_byte_to_vm(vm, (address + i), (char)write);
		write >>= 4;
		i++;
	}
}
