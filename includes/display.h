/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 15:44:59 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/05 21:40:07 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# define MEM_H (MEM_SIZE / 64)
# define MEM_W ((MEM_SIZE / 64) * 3)

void				display_memory(t_vm *vm, int pc);
void				init_memory_win(t_win *memory);
void				init_ncurse_display(t_vm *vm);

#endif
