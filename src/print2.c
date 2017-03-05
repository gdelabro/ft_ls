/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 13:17:46 by gdelabro          #+#    #+#             */
/*   Updated: 2017/02/28 15:19:59 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

void	ft_print_nol(char *name, t_ls u)
{
	(u.index - 1) % 8 == 0 && u.index != 1 ? ft_putendl("") : 0;
	ft_color(u.st.st_mode);
	ft_putstr(name);
	ft_putstr(NONE);
	ft_space(u.e.name, u.e.n_len);
	ft_putstr(" ");
}

void	ft_color(mode_t mode)
{
	S_ISBLK(mode) ? ft_putstr(DEV_B) : NULL;
	S_ISCHR(mode) ? ft_putstr(DEV_C) : NULL;
	S_ISDIR(mode) ? ft_putstr(CYAN) : NULL;
	S_ISFIFO(mode) ? ft_putstr(BROWN) : NULL;
	S_ISREG(mode) ? ft_putstr(NONE) : NULL;
	S_ISLNK(mode) ? ft_putstr(MAGENTA) : NULL;
	S_ISSOCK(mode) ? ft_putstr(GREEN) : NULL;
}

void	ft_space(char *str, size_t len)
{
	while (len-- > ft_strlen(str))
		ft_putchar(' ');
}

void	ft_print_l(t_info e, t_ls u)
{
	ft_putstr(e.droit);
	e.droit[0] == 'c' ? ft_putstr("  ") : ft_putstr("  ");
	ft_space(e.noeud, e.noeud_len);
	ft_putstr(e.noeud);
	ft_putstr(" ");
	ft_putstr(u.pwd->pw_name);
	ft_space(u.pwd->pw_name, e.pw_len);
	ft_putstr("  ");
	ft_putstr(e.grp);
	ft_space(e.grp, e.grp_len);
	ft_putstr("  ");
	ft_space(e.taille, e.taille_len);
	ft_putstr(e.taille);
	ft_putstr(" ");
	ft_putstr(e.date);
	ft_putstr(" ");
	ft_color(u.st.st_mode);
	ft_putstr(e.name);
	ft_putstr(NONE);
	u.tmp = name_link(u.name);
	S_ISLNK(u.st.st_mode) ? ft_putstr(" -> ") : 0;
	S_ISLNK(u.st.st_mode) ? ft_putstr(u.tmp) : 0;
	ft_strdel(&u.tmp);
	ft_putendl("");
}

char	*ft_name(char *rep1, char *rep2)
{
	char	*name;
	char	*tmp;

	if (rep1 && rep2)
	{
		if (ft_strcmp(rep1, "/"))
		{
			!(tmp = ft_strjoin(rep1, "/")) ? ft_quit(2, ' ') : 0;
			!(name = ft_strjoin(tmp, rep2)) ? ft_quit(2, ' ') : 0;
			ft_strdel(&tmp);
		}
		else
			!(name = ft_strjoin("/", rep2)) ? ft_quit(2, ' ') : 0;
	}
	else
	{
		!(tmp = ft_strdup(rep2)) ? ft_quit(2, ' ') : 0;
		return (tmp);
	}
	return (name);
}
