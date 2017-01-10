/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 23:17:16 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/10 16:49:45 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/include/libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <time.h>
# include <stdio.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>

# ifdef NOCOLOR
#  define C_RESET	""
#  define C_BOLD	""
#  define C_RED		""
#  define C_GREEN	""
#  define C_BROWN	""
#  define C_BLUE	""
#  define C_MAGENTA	""
#  define C_CYAN	""
# endif

# ifdef COLOR
#  define C_RESET	"\x1B[0m"
#  define C_BOLD	"\x1B[1m"
#  define C_RED		"\x1B[31m"
#  define C_GREEN	"\x1B[32m"
#  define C_BROWN	"\x1B[33m"
#  define C_BLUE	"\x1B[34m"
#  define C_MAGENTA	"\x1B[35m"
#  define C_CYAN	"\x1B[36m"
# endif

typedef struct		s_opt
{
	char			l;
	char			upper_r;
	char			upper_s;
	char			a;
	char			r;
	char			t;
	char			u;
	char			f;
	char			g;
	char			c;
}					t_opt;

typedef struct		s_elem
{
	char			*name;
	char			*path;
	time_t			date;
	mode_t			st_mode;
	nlink_t			st_nlink;
	uid_t			st_uid;
	gid_t			st_gid;
	off_t			st_size;
	quad_t			st_blocks;
	dev_t			st_rdev;
	struct s_elem	*next;
}					t_elem;

typedef struct		s_size
{
	int				total;
	int				size;
	int				groupspace;
	int				userspace;
	int				linkspace;
	int				min;
	int				maj;
}					t_size;

void				error_arg(char arg);
void				basicerror(char *name, char *error, int ex);
void				core(t_opt arg, t_list *path, int multidir, t_list *file);
void				display_file(t_opt arg, t_elem *files, int fileordir);
void				recursion(t_opt arg, t_elem *files);
void				ls_simple(t_opt arg, t_elem *files);
void				ls_long(t_opt arg, t_elem *files, int fileordir);
void				sort(t_elem **list, int (*cmp)());
void				reversesort(t_elem **list);
void				display_date(time_t date);
void				print_access(t_elem *elem);
void				print_int(int nlink, int spacemax);
void				print_str(char *str, int spacemax);
void				print_majmin(t_elem *file, t_size size);
void				free_elem(t_elem **elem);
void				free_list(t_list **elem);
void				print_link(t_elem *cur);
void				free_argv(char ***argv);
void				print_minmaj_space(t_size size);
void				swap_elem(t_elem **a, t_elem **b);
void				swap_list(t_list **elem1, t_list **elem2);
void				sort_argv(t_list **path);
void				elem_cpy(t_elem **src, t_elem *cpy);
void				display_file(t_opt arg, t_elem *files, int fileordir);
void				elemgetfiles(t_elem **files, char *name, char *path, \
						t_opt arg);
int					cmp_alpha(t_elem *elem1, t_elem *elem2);
int					cmp_time(t_elem *elem1, t_elem *elem2);
int					cmp_size(t_elem *elem1, t_elem *elem2);
int					elemget(t_elem **files, struct dirent *file, char *path, \
						t_opt arg);
char				checkminmaj(t_elem *files);
char				check_link(char *path);
char				is_link(char *path, t_opt arg);
t_elem				*sort_elem(t_elem *list, t_opt arg);
t_size				get_size(t_opt arg, t_elem *files);

#endif
