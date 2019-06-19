/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:55:22 by vlambert          #+#    #+#             */
/*   Updated: 2019/06/19 11:31:20 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

/*
**Errors codes
**Corresponding message
*/

# define USAGE				0
# define USAGE_MSG			"Usage: ./corewar [-d -v -V] [-dump nbr_cycles] \
[[-n number] champion1.cor] ...\n-d: Debug mode\n-v: Verbose mode\n\
-V: Visual mode\n"

# define ERR_DBLDUMP		1
# define ERR_DBLDUMP_MSG	"There are more than one dump precised\n"

# define ERR_DUMPVAL		2
# define ERR_DUMPVAL_MSG	"The dump nbr_cycles is lower than \
one or missing\n\0"

# define ERR_BADARG			3
# define ERR_BADARG_MSG		"Unknown argument\n"

# define ERR_BADNBR			4
# define ERR_BADNBR_MSG		"The player number is lower than 1 or \
missing or the same than another player\n"

# define ERR_TWONBR			5
# define ERR_TWONBR_MSG		"Two player number were precised \
for a single player\n"

/*
**Errors message max size
*/

# define ERR_MSG_SIZE		256

#endif
