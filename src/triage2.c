/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triage2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 18:45:55 by gdelabro          #+#    #+#             */
/*   Updated: 2017/02/14 17:02:52 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

void	makefile_first(char **str)
{
	int		i;
	int		i2;
	char	*tmp;

	i = -1;
	i2 = -1;
	while (str[++i] && (i2 = i) != -1)
		while (str[++i2])
		{
			if (!ft_strcmp(str[i2], "Makefile"))
			{
				tmp = str[i];
				str[i] = str[i2];
				str[i2] = tmp;
			}
		}
}

void	ft_swap(char **str1, char **str2)
{
	char *tmp;

	tmp = *str1;
	*str1 = *str2;
	*str2 = tmp;
}
