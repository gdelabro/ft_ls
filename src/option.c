/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 16:20:21 by gdelabro          #+#    #+#             */
/*   Updated: 2017/02/28 15:18:33 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

void		u_init(t_ls *u)
{
	u->e.taille_len = 0;
	u->e.noeud_len = 0;
	u->e.pw_len = 0;
	u->e.grp_len = 0;
	u->e.n_len = 0;
	u->total = 0;
	u->to_print = NULL;
	u->i = -1;
	u->index = 0;
}

void		permission(t_ls *u, char *dir)
{
	u->name = ft_strdup(dir);
	lstat(u->name, &u->st);
	u->e.name = ft_strcpyend(dir, '/');
	u->e.droit = ft_droit(u->st.st_mode);
	u->e.droit[0] == 'd' ? ft_putendl_fd("", 2) : 0;
	u->e.droit[0] == 'd' ? ft_putstr_fd(dir, 2) : 0;
	u->e.droit[0] == 'd' ? ft_putendl_fd(":", 2) : 0;
	u->e.droit[0] == 'd' ? ft_putstr_fd("ft_ls: ", 2) : 0;
	u->e.droit[0] == 'd' ? perror(u->e.name) : 0;
	ft_strdel(&u->e.droit);
	ft_strdel(&u->e.name);
	ft_strdel(&u->name);
	ft_strdel(&dir);
}

char		**ft_remplir(int i, char **tab)
{
	int		taille;
	char	**tab2;

	taille = 0;
	while (tab[i + taille])
		taille++;
	!(tab2 = (char**)malloc(sizeof(*tab2) * taille + 1)) ? ft_quit(2, ' ') : 0;
	taille = -1;
	i -= 1;
	while (tab[++i])
		!(tab2[++taille] = ft_strdup(tab[i])) ? ft_quit(2, ' ') : 0;
	tab2[++taille] = NULL;
	return (tab2);
}

void		t_init(t_option *t)
{
	t->i = 0;
	t->str = NULL;
	t->a = 0;
	t->r1 = 0;
	t->opt = 1;
	t->r2 = 0;
	t->l = 0;
	t->t = 0;
}

t_option	option(char **argv)
{
	t_option t;

	t_init(&t);
	while (argv[++t.i] && !(t.i2 = 0))
	{
		if (argv[t.i][0] == '-' && t.opt == 1)
			while (argv[t.i][++t.i2])
			{
				argv[t.i][t.i2] == 'a' ? t.a = 1 : 0;
				argv[t.i][t.i2] == 'R' ? t.r2 = 1 : 0;
				argv[t.i][t.i2] == 'r' ? t.r1 = 1 : 0;
				argv[t.i][t.i2] == 'l' ? t.l = 1 : 0;
				argv[t.i][t.i2] == 't' ? t.t = 1 : 0;
				t.q = argv[t.i][t.i2];
				t.q != 'a' && t.q != 'R' && t.q != 'r' && t.q != 'l' &&
				t.q != 't' ? ft_quit(1, argv[t.i][t.i2]) : 0;
			}
		else if (!(t.opt = 0)
				&& (t.str = ft_remplir(t.i, argv)))
			break ;
	}
	return (t);
}
