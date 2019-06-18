/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:23:18 by vlambert          #+#    #+#             */
/*   Updated: 2019/06/18 13:21:01 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "../includes/op.h"

typedef struct      s_player
{
    int     number;
    int     lives;
    int     last_lives;
    int     alive;
    char    name[PROG_NAME_LENGTH];
    char    comment[COMMENT_LENGTH];
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
    int             players_nbr;
    int             carry;
    char            err[10][500];
}                   t_vm;

int         options(int ac, char *av[], t_vm *vm);

#endif