/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 03:26:55 by vdarmaya          #+#    #+#             */
/*   Updated: 2016/12/14 00:06:59 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include "../libft/include/libft.h"

typedef struct dirent	t_dirent;
typedef struct stat t_stat;

typedef	struct		s_opt
{
	char			set_a;
	char			set_l;
	char			set_r;
	char			set_rmaj;
	char			set_t;
}					t_opt;

typedef struct		s_lstent
{
	struct dirent	*ent;
	struct s_lstent	*next;
}					t_lstent;

char				is_valide(char *path);
char				**sort_argv(int argc, char **argv, t_opt *opt);
void				invalid(char c);
void				go_core(int argc, char **argv);
void				del(void *name, size_t content_size);
void				print_normal(t_lstent *lst);
void				free_lstent(t_lstent **lst);
void				treat_current(char *str, t_opt *opt);
void				treat_normal(int argc, char **argv, int invalid);
void				treat_with_opt(int argc, char **str, t_opt *opt, int inv);
void				treat_single_opt(t_opt *opt, int inv);
void				print_name(char *str);
void				print_invalid(char *str);
void				go_recur(char *path, t_opt *opt, int i);
int					check_dir_validity(int i, int argc, char **argv,
						t_list	*entity);
t_opt				*new_opt();
t_lstent			*new_lstent(t_dirent *entity);
t_lstent			*sort_ascii(DIR *dir, char point);
t_lstent			*sort_opt(DIR *dir, t_opt *opt, char *path);
t_lstent			*sort_time(DIR *dir, char point, char *path);

#endif
