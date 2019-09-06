/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocp_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 17:33:31 by bopopovi          #+#    #+#             */
/*   Updated: 2019/09/06 20:34:06 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

int		get_param_type_from_ocp(char ocp, int param_position)
{
	return (ocp >> (8 - param_position * 2) & 0x03);
}

void	set_params(t_param *param, t_op op, char ocp)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (op.has_ocp)
			param[i].type = get_param_type_from_ocp(ocp, (i + 1));
		else
		{
			if (i == op.arg_nbr)
				return ;
			if (op.arg_types[i] == T_REG)
				param[i].type = REG_CODE;
			else if (op.arg_types[i] == T_IND)
				param[i].type = IND_CODE;
			else if (op.arg_types[i] == T_DIR)
				param[i].type = DIR_CODE;
		}
		i++;
	}
}

int		ocp_match_instruction_params(t_op op, char ocp, t_vm *vm)
{
	int		param_type;
	int		i;

	param_type = 0;
	i = 0;
	local_dbg(vm->options & OPTD, "\nChecking OCP (%d arguments):\n",
		op.arg_nbr);
	while (i < op.arg_nbr)
	{
		param_type = get_param_type_from_ocp(ocp, i + 1);
		i++;
	}
	local_dbg(vm->options & OPTD, "\n");
	return (1);
}
