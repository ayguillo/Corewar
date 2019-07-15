/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocp_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 17:33:31 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/15 17:19:50 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

static bool l_dbg = 1;

int		get_param_type_from_ocp(char ocp, int param_position)
{
	return (ocp >> (8 - param_position * 2) & 0x03);
}

void	set_params_from_ocp(t_param *param, char ocp, int nbr_of_params)
{
	int i;

	i = 0;
	while (i < nbr_of_params)
	{
		param[i].type = get_param_type_from_ocp(ocp, (i + 1));
		local_dbg(l_dbg, "\tOCP %d : %d\n", i + 1, param[i].type);
		i++;
	}
}

int		ocp_match_instruction_params(t_op op, char ocp)
{
	int		param_type;
	int 	i;

	param_type = 0;
	i = 0;
	local_dbg(l_dbg, "\nOCP CHECK :\n");
	while (i < op.arg_nbr)
	{
		param_type = get_param_type_from_ocp(ocp, i + 1);
		local_dbg(l_dbg, "Available params : %b\n", op.arg_types[i]);
		local_dbg(l_dbg, "\t%b == %b ?\n", (param_type & op.arg_types[i]), param_type);
		if ((param_type & op.arg_types[i]) != param_type)
			return (0);
		i++;
	}
	return (1);
}
