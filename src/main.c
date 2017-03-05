/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 13:32:26 by gdelabro          #+#    #+#             */
/*   Updated: 2017/02/28 15:56:10 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

void		ft_quit(int i, char a)
{
	char str[2];

	str[0] = a;
	str[1] = 0;
	if (i == 1)
	{
		ft_putendl_fd(ft_strjoin("ft_ls: illegal option -- ", str), 2);
		ft_putendl_fd("usage: ft_ls [-Ralrt] [file ...]", 2);
	}
	if (i == 2)
		ft_putendl_fd("malloc fail ... end of process", 2);
	exit(1);
}

char		**add_str(char **tab, char *str)
{
	int		i;
	int		len;
	char	**n;

	len = 0;
	if (tab)
		while (tab[len])
			++len;
	!(n = (char**)malloc(sizeof(char*) * ++len + 1)) ? ft_quit(2, ' ') : 0;
	n[len] = NULL;
	i = 0;
	if (tab)
	{
		while (i < len - 1)
		{
			!(n[i] = ft_strdup(tab[i])) ? ft_quit(2, ' ') : 0;
			ft_strdel(&tab[i++]);
		}
	}
	!(n[i] = ft_strdup(str)) ? ft_quit(2, ' ') : 0;
	free(tab);
	tab = NULL;
	return (n);
}

void		ft_ls(t_option t)
{
	t_ls	u;

	if (!t.str)
		print_dir(ft_strdup("."), t);
	else
	{
		u_init(&u);
		file_dir_to_print(&u, t);
		u.i = -1;
		while (u.to_print && u.to_print[++u.i])
		{
			print_file(&u, t, u.to_print[u.i], NULL);
			ft_strdel(&u.to_print[u.i]);
		}
		t.l == 0 && u.to_print ? ft_putendl("") : 0;
		u.to_print && u.dir_to_print ? ft_putendl("") : 0;
		u.i = -1;
		while (u.dir_to_print && u.dir_to_print[++u.i])
			print_dir(u.dir_to_print[u.i], t);
	}
}

int			main(int argc, char **argv)
{
	t_option	t;

	(void)argc;
	t = option(argv);
	ft_ls(t);
	return (0);
}
