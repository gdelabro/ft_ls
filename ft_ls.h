/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdelabro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 13:27:56 by gdelabro          #+#    #+#             */
/*   Updated: 2017/02/28 15:15:44 by gdelabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>
# include "libft/libft.h"

# define NONE			"\033[0m"
# define BOLD			"\033[1m"
# define BLACK			"\033[30m"
# define RED			"\033[31m"
# define GREEN			"\033[32m"
# define BROWN			"\033[33m"
# define BLUE			"\033[34m"
# define MAGENTA		"\033[35m"
# define CYAN			"\033[36;1m"
# define GRAY			"\033[37m"
# define DEV_C			"\033[43;34m"
# define DEV_B			"\033[46;34m"

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;
typedef struct passwd	t_passwd;
typedef struct group	t_group;

typedef struct	s_info
{
	char	*name;
	char	*date;
	char	*droit;
	char	*taille;
	size_t	taille_len;
	char	*grp;
	size_t	grp_len;
	char	*noeud;
	size_t	noeud_len;
	size_t	pw_len;
	size_t	n_len;
}				t_info;

typedef struct	s_option
{
	int		a;
	int		r1;
	int		r2;
	int		l;
	int		t;
	int		i;
	int		i2;
	int		opt;
	char	**str;
	char	q;
}				t_option;

typedef struct	s_ls
{
	DIR			*rep;
	t_info		e;
	t_stat		st;
	t_dirent	*fichier;
	t_group		*gr;
	t_passwd	*pwd;
	char		*name;
	int			i;
	char		*tmp;
	int			index;
	int			total;
	char		**to_print;
	char		**dir_to_print;
}				t_ls;

t_option		option(char **argv);
void			ft_quit(int i, char a);
void			ft_ls(t_option t);
char			**remplir(int i, char **tab);
int				match(char *s1, char *s2);
int				match2(char *s1, char **tab);
int				remplir_info(t_ls *u, char *dir);
char			*ft_name(char *rep1, char *rep2);
char			**add_str(char **tab, char *str);
void			free_info(t_ls *u);
void			ft_color(mode_t mode);
void			ft_print_l(t_info e, t_ls u);
void			ft_print_nol(char *name, t_ls u);
void			print_file(t_ls *u, t_option t, char *name, char *dir);
void			print_dir(char *dir, t_option t);
void			permission(t_ls *u, char *dir);
void			ft_space(char *str, size_t len);
void			remplir_taille(t_ls *u, t_info e);
char			*ft_droit(mode_t mode);
char			*ft_date(char *date);
char			*name_link(char *name);
void			u_init(t_ls *u);
void			file_dir_to_print(t_ls *u, t_option t);
void			major_minor(t_ls *u);
void			triage(char **str, t_option t, char *dir);
int				is_something(char *name);
void			makefile_first(char **str);
void			ft_swap(char **str1, char **str2);

#endif
