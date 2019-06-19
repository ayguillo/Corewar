/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reversebyte.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 14:04:27 by ayguillo          #+#    #+#             */
/*   Updated: 2019/06/19 14:06:06 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_reversebyte(unsigned int byte)
{
	unsigned int	revbyte;
	int				i;

	i = 3;
	while (i >= 0)
	{
		((char*)(&revbyte))[i] = ((char*)(&byte))[0];
		byte = byte >> 8;
		i--;
	}
	return (revbyte);
}
