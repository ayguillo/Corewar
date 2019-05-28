/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 16:17:16 by vlambert          #+#    #+#             */
/*   Updated: 2018/11/29 14:05:55 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*temp;

	if (!(lst) || !(*f))
		return (NULL);
	temp = (*f)(lst);
	if (!(temp = ft_lstnew(temp->content, temp->content_size)))
		return (NULL);
	temp->next = ft_lstmap(lst->next, f);
	if (!temp->next && lst->next)
	{
		free(temp->content);
		free(temp);
		temp = NULL;
	}
	return (temp);
}
