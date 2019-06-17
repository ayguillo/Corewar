/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:23:18 by vlambert          #+#    #+#             */
/*   Updated: 2019/06/17 12:28:39 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "../includes/op.h"

# define MAX_PLAYERS 4

typedef struct      s_player
{
    int number;
    int lives;
    int last_lives;
    int alive;
}                   t_player;

typedef struct      s_vm
{
    unsigned char   mem[MEM_SIZE];
    t_player        players[MAX_PLAYERS];
    int             player_turn;
    int             cycles;
    int             cycle_to_die;
    int             cycles_limit;
    int             options;
}                   t_vm;


#endif