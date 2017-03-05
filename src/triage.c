/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 15:33:41 by gdelabro          #+#    #+#             */
/*   Updated: 2017/02/14 15:23:51 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

void	tri_normale(char **str)
{
	int		i;
	int		i2;
	char	*tmp;

	i = -1;
	i2 = -1;
	makefile_first(str);
	while (str[++i] && (i2 = i) != -1)
		while (str[++i2])
		{
			if (ft_strcmp(str[i], str[i2]) > 0 &&
					ft_strcmp(str[i], "Makefile"))
			{
				tmp = str[i];
				str[i] = str[i2];
				str[i2] = tmp;
			}
		}
}

int		date(char *name)
{
	t_stat st;

	lstat(name, &st);
	return (st.st_mtime);
}

void	tri_time1(char **str, char *dir)
{
	int		i;
	int		i2;
	char	*tmp1;
	char	*tmp2;

	i = -1;
	i2 = -1;
	while (str[++i] && (i2 = i) != -1)
		while (str[++i2])
		{
			tmp1 = ft_name(dir, str[i]);
			tmp2 = ft_name(dir, str[i2]);
			if (date(tmp1) < date(tmp2))
				ft_swap(&str[i], &str[i2]);
			else if (date(tmp1) == date(tmp2) &&
					ft_strcmp(str[i], str[i2]) > 0)
				ft_swap(&str[i], &str[i2]);
			ft_strdel(&tmp1);
			ft_strdel(&tmp2);
		}
}

void	tri_reverse(char **str)
{
	int		i;
	int		i2;
	char	*tmp;

	i2 = -1;
	i = -1;
	while (str && str[++i2])
		;
	i2 != -1 ? --i2 : 0;
	while (str && ++i <= i2 / 2)
	{
		tmp = str[i];
		str[i] = str[i2 - i];
		str[i2 - i] = tmp;
	}
}

void	triage(char **str, t_option t, char *dir)
{
	str ? tri_normale(str) : 0;
	t.t == 1 && str ? tri_time1(str, dir) : 0;
	t.r1 == 1 && str ? tri_reverse(str) : 0;
}
