/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 16:06:32 by gdelabro          #+#    #+#             */
/*   Updated: 2017/02/28 15:18:58 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

void	file_dir_to_print(t_ls *u, t_option t)
{
	u->to_print = NULL;
	u->dir_to_print = NULL;
	u->i = -1;
	while (t.str[++u->i])
	{
		if (lstat(t.str[u->i], &u->st) == 0)
			S_ISDIR(u->st.st_mode) ?
			u->dir_to_print = add_str(u->dir_to_print, t.str[u->i]) :
			(u->to_print = add_str(u->to_print, t.str[u->i]));
		else
		{
			ft_putstr_fd("ft_ls: ", 2);
			perror(t.str[u->i]);
		}
		ft_strdel(&t.str[u->i]);
	}
	triage(u->to_print, t, NULL);
	triage(u->dir_to_print, t, NULL);
}

void	insert_itoa(char *str, int nb, int i)
{
	while (nb)
	{
		i >= 0 && i < (int)ft_strlen(str) ? str[i--] = nb % 10 + 48 : 0;
		nb /= 10;
	}
}

void	major_minor(t_ls *u)
{
	int i;

	i = -1;
	ft_strdel(&u->e.taille);
	!(u->e.taille = ft_strnew(9)) ? ft_quit(2, ' ') : 0;
	u->e.taille[8] = 0;
	while (++i < 8)
		u->e.taille[i] = ' ';
	u->e.taille[3] = ',';
	insert_itoa(u->e.taille, major(u->st.st_rdev), 2);
	insert_itoa(u->e.taille, minor(u->st.st_rdev), 7);
}
