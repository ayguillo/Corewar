/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_options.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:28:13 by vlambert          #+#    #+#             */
/*   Updated: 2019/06/17 12:21:07 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/options.h"
#include "../includes/vm.h"
#include "../libft/libft.h"
#include "../includes/errors.h"

static int opt_dump(int ac, char *av[], t_vm *vm, int i)
{
    if (vm->cycles_limit)
        return (ERR_DBLDUMP);
    if (i + 1 < ac && ft_atoi(av[i + 1]) > 0)
        vm->cycles_limit = ft_atoi(av[i + 1]);
    else
        return (ERR_DUMPVAL);
}

static int opt_n(int ac, char *av[], t_vm *vm, int i)
{
}

static int opt_others(int ac, char *av[], t_vm *vm, int i)
{
    int j;

    j = 0;
    while (av[i][++j])
    {
        if (av[i][j] == 'V')
            vm->options = vm->options & OPTMAJV;
        else if (av[i][j] == 'v')
            vm->options = vm->options & OPTV;
        else if (av[i][j] == 'd')
            vm->options = vm->options & OPTD;
        else
            return (ERR_BADARG);
    }
}

int options(int ac, char *av[], t_vm *vm)
{
    int i;
    int ret;

    i = 0;
    while (++i < ac)
    {
        if (av[i][0] = '-')
        {
            if (!ft_strcmp(av[i], "dump"))
            {
                if ((ret = dump(ac, av, vm, i)))
                    return ret;
            }
            else if (av[i][1] == 'n')
            {
            }
            else
            {
            }
        }
    }
}