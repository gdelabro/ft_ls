/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 18:45:55 by gdelabro          #+#    #+#             */
/*   Updated: 2016/11/09 14:48:19 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbmot(char const *s, char c)
{
	int i;
	int nb;

	nb = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] == c && s[i + 1] != c && s[i + 1]) || (i == 0 && s[i] != c))
			nb++;
		i++;
	}
	return (nb);
}

static int	ft_remplir(char const *s, char c, int i)
{
	char	*str;
	int		i2;
	int		i3;

	i2 = 0;
	if (s[i] == c)
		i++;
	i3 = i;
	while (s[i] != c && s[i])
	{
		i2++;
		i++;
	}
	str = (char*)malloc(sizeof(*str) * i2 + 1);
	if (!str)
		return (0);
	i2 = 0;
	while (s[i3] && s[i3] != c)
		str[i2++] = s[i3++];
	str[i2] = '\0';
	return (i2);
}

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	int		i2;
	char	**tab;

	if (!s)
		return (NULL);
	i2 = 0;
	i = 0;
	tab = (char**)malloc(sizeof(*tab) * ft_nbmot(s, c) + 1);
	if (!tab)
		return (NULL);
	while (s[i])
	{
		if (i == 0 && s[i] != c)
			i2 = 1;
		else if ((s[i] == c && s[i + 1] != c) && (s[i + 1]))
			tab[i2++] = ft_strsub(s, i + 1, ft_remplir(s, c, i));
		i++;
	}
	if (s[0] != c)
		tab[0] = ft_strsub(s, 0, ft_remplir(s, c, 0));
	tab[i2] = 0;
	if (!tab)
		return (NULL);
	return (tab);
}
