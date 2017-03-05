/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 16:36:23 by gdelabro          #+#    #+#             */
/*   Updated: 2017/02/28 15:55:31 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

char		*name_link(char *name)
{
	char	*tmp;
	int		len;

	!(tmp = (char*)malloc(sizeof(char) * 256)) ? ft_quit(2, ' ') : 0;
	ft_bzero(tmp, 256);
	len = readlink(name, tmp, 256);
	return (tmp);
}

void		print_file(t_ls *u, t_option t, char *name, char *dir)
{
	!(u->name = ft_strdup(name)) ? ft_quit(2, ' ') : 0;
	remplir_info(u, dir);
	++u->index;
	t.l == 1 && u->gr && u->pwd ? ft_print_l(u->e, *u) : 0;
	t.l == 0 && u->gr && u->pwd ? ft_print_nol(u->e.name, *u) : 0;
	u->tmp = ft_strcpyend(u->name, '/');
	!u->gr || !u->pwd ? ft_putstr_fd("ft_ls: ", 2) : 0;
	!u->gr || !u->pwd ? perror(u->tmp) : 0;
	ft_strdel(&u->tmp);
	free_info(u);
}

void		print_dir2(char *dir, t_option t, t_ls u, char **to_print)
{
	static int	i = 0;
	char		*tmp;

	u.i = -1;
	++i != 1 ? ft_putendl("") : 0;
	ft_putstr(dir);
	ft_putendl(":");
	if (to_print)
	{
		t.l == 1 ? ft_putstr("total ") : 0;
		t.l == 1 ? ft_putendl(tmp = ft_itoa(u.total)) : 0;
		t.l == 1 ? ft_strdel(&tmp) : 0;
		while (to_print[++u.i])
			print_file(&u, t, to_print[u.i], dir);
		t.l == 0 ? ft_putendl("") : 0;
		u.i = -1;
		while (t.r2 == 0 && to_print[++u.i])
			ft_strdel(&to_print[u.i]);
		while (t.r2 == 1 && to_print[++u.i])
		{
			ft_strcmp(".", to_print[u.i]) && ft_strcmp("..", to_print[u.i])
				? print_dir(ft_name(dir, to_print[u.i]), t) : 0;
			ft_strdel(&to_print[u.i]);
		}
	}
}

void		print_dir(char *dir, t_option t)
{
	t_ls		u;
	char		**to_print;

	to_print = NULL;
	!(u.rep = opendir(dir)) ? permission(&u, dir) : 0;
	if (!u.rep)
		return ;
	u_init(&u);
	while ((u.fichier = readdir(u.rep)) != NULL)
		if (u.fichier->d_name[0] != '.' || t.a == 1)
		{
			!(u.name = ft_strdup(u.fichier->d_name)) ? ft_quit(2, ' ') : 0;
			remplir_info(&u, dir);
			to_print = add_str(to_print, u.fichier->d_name);
			free_info(&u);
		}
	triage(to_print, t, dir);
	print_dir2(dir, t, u, to_print);
	ft_strdel(&dir);
	free(to_print);
	to_print = NULL;
	closedir(u.rep);
}
