/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_query.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:27:12 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/01 20:24:35 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/proc.h"

int		player_exist(t_vm *vm, int player_id)
{
	if (player_id - 1 <= vm->players_nbr/* && vm->players[player_id] != 0*/)
		return (1);
	return (0);
}
