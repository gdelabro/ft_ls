/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 16:34:25 by gdelabro          #+#    #+#             */
/*   Updated: 2017/02/28 15:35:39 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

char	*ft_date(char *date)
{
	char	*date2;
	int		i;

	i = -1;
	date2 = ft_strnew(12);
	while (++i < 12)
		date2[i] = date[i + 4];
	date2[12] = 0;
	return (date2);
}

void	remplir_taille(t_ls *u, t_info e)
{
	ft_strlen(e.taille) > e.taille_len ?
		u->e.taille_len = ft_strlen(e.taille) : 0;
	ft_strlen(e.grp) > e.grp_len ?
		u->e.grp_len = ft_strlen(e.grp) : 0;
	ft_strlen(e.noeud) > e.noeud_len ?
		u->e.noeud_len = ft_strlen(e.noeud) : 0;
	ft_strlen(u->pwd->pw_name) > e.pw_len ?
		u->e.pw_len = ft_strlen(u->pwd->pw_name) : 0;
	ft_strlen(u->e.name) > e.n_len ?
		u->e.n_len = ft_strlen(u->e.name) : 0;
}

char	*ft_droit(mode_t mode)
{
	char	*droit;

	!(droit = (char*)malloc(sizeof(char) * 11)) ? ft_quit(2, ' ') : 0;
	droit[10] = 0;
	droit[0] = S_ISDIR(mode) ? 'd' : '-';
	S_ISCHR(mode) ? droit[0] = 'c' : 0;
	S_ISFIFO(mode) ? droit[0] = 'p' : 0;
	S_ISBLK(mode) ? droit[0] = 'b' : 0;
	S_ISLNK(mode) ? droit[0] = 'l' : 0;
	S_ISSOCK(mode) ? droit[0] = 's' : 0;
	droit[1] = S_IRUSR & mode ? 'r' : '-';
	droit[2] = S_IWUSR & mode ? 'w' : '-';
	droit[3] = S_IXUSR & mode ? 'x' : '-';
	droit[4] = S_IRGRP & mode ? 'r' : '-';
	droit[5] = S_IWGRP & mode ? 'w' : '-';
	droit[6] = S_IXGRP & mode ? 'x' : '-';
	droit[7] = S_IROTH & mode ? 'r' : '-';
	droit[8] = S_IWOTH & mode ? 'w' : '-';
	droit[9] = S_IXOTH & mode ? 'x' : '-';
	return (droit);
}

void	free_info(t_ls *u)
{
	ft_strdel(&u->e.date);
	ft_strdel(&u->e.taille);
	ft_strdel(&u->e.droit);
	ft_strdel(&u->e.noeud);
	ft_strdel(&u->name);
	ft_strdel(&u->e.name);
}

int		remplir_info(t_ls *u, char *dir)
{
	!(u->e.name = ft_strdup(u->name)) ? ft_quit(2, ' ') : 0;
	ft_strdel(&u->name);
	!(u->name = ft_name(dir, u->e.name)) ? ft_quit(2, ' ') : 0;
	lstat(u->name, &u->st);
	u->total += u->st.st_blocks;
	!(u->e.noeud = ft_itoa((long)u->st.st_nlink)) ? ft_quit(2, ' ') : 0;
	!(u->e.date = ft_date(ctime(&u->st.st_mtime))) ? ft_quit(2, ' ') : 0;
	!(u->e.taille = ft_itoa(u->st.st_size)) ? ft_quit(2, ' ') : 0;
	!(u->e.droit = ft_droit(u->st.st_mode)) ? ft_quit(2, ' ') : 0;
	u->e.droit[0] == 'c' || u->e.droit[0] == 'b' ? major_minor(u) : 0;
	u->gr = getgrgid(u->st.st_gid);
	u->pwd = getpwuid(u->st.st_uid);
	u->gr ? u->e.grp = u->gr->gr_name : 0;
	u->gr && u->pwd ? remplir_taille(u, u->e) : 0;
	return (1);
}
