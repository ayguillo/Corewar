/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitandspaces.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 11:44:13 by ayguillo          #+#    #+#             */
/*   Updated: 2019/06/05 11:42:24 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_words_l(char const *s, char c)
{
	int i;

	i = 0;
	while (((s[i] < 9 || s[i] > 13) && s[i] != 32 && s[i] != c) && s[i] != '\0')
		i++;
	i++;
	return (i);
}

static int	ft_count_w(char const *s, char c)
{
	int i;
	int count_word;
	int is_word;

	i = 0;
	count_word = 0;
	is_word = 0;
	while (s[i])
	{
		if (((s[i] < 9 || s[i] > 13) && s[i] != 32 && s[i] != c)
				&& is_word == 0)
		{
			is_word = 1;
			count_word++;
		}
		else if ((((s[i] >= 9 && s[i] <= 13)) || s[i] == 32
					|| s[i] == c) && is_word == 1)
			is_word = 0;
		i++;
	}
	count_word++;
	return (count_word);
}

char		**ft_splitandspaces(char const *s, char c)
{
	int		n;
	int		i;
	int		j;
	char	**tab;

	n = -1;
	i = 0;
	j = 0;
	if (!s || !c)
		return (NULL);
	if (!(tab = (char**)malloc(sizeof(char*) * ft_count_w(s, c))))
		return (NULL);
	while (s[++n])
		if ((s[n] < 9 || s[n] > 13) && s[n] != 32 && s[n] != c)
		{
			if (!(tab[i] = (char*)malloc(sizeof(char) * ft_words_l(&s[n], c))))
				return (NULL);
			while (((s[n] < 9 || s[n] > 13) && s[n] != 32 && s[n] != c) && s[n])
				tab[i][j++] = s[n++];
			tab[i++][j] = '\0';
			j = 0;
			n--;
		}
	tab[i] = NULL;
	return (tab);
}
