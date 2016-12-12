/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 21:32:32 by vdarmaya          #+#    #+#             */
/*   Updated: 2016/12/13 00:52:42 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h>
#include "../includes/ft_ls.h"

char	contain(char **s1, char *str, int inc, char opt)
{
	int		i;

	i = 0;
	if (opt)
		i++;
	while (++i < inc)
	{
		if (!ft_strcmp(s1[i], str))
			return (1);
	}
	return (0);
}

char	**sort_argv_opt(int argc, char **argv)
{
	int		i;
	int		j;
	char	**str;
	char	*tmp;

	str = (char**)malloc(sizeof(char*) * (argc + 1));
	str[0] = ft_strdup(argv[0]);
	str[1] = ft_strdup(argv[1]);
	str[argc] = NULL;
	i = 1;
	while (++i < argc)
	{
		j = 1;
		tmp = NULL;
		while (argv[++j])
		{
			if (!tmp && !contain(str, argv[j], i, 1))
				tmp = argv[j];
			else if (tmp && ft_strcmp(tmp, argv[j]) >= 0 && !contain(str, argv[j], i, 1))
				tmp = argv[j];
		}
		str[i] = ft_strdup(tmp);
	}
	return (str);
}

char	**sort_argv(int argc, char **argv, t_opt *opt)
{
	int		i;
	int		j;
	char	**str;
	char	*tmp;

	if (opt)
		return (sort_argv_opt(argc, argv));
	str = (char**)malloc(sizeof(char*) * (argc + 1));
	str[0] = ft_strdup(argv[0]);
	str[argc] = NULL;
	i = 0;
	while (++i < argc)
	{
		j = 0;
		tmp = NULL;
		while (argv[++j])
		{
			if (!tmp && !contain(str, argv[j], i, 0))
				tmp = argv[j];
			else if (tmp && ft_strcmp(tmp, argv[j]) >= 0 && !contain(str, argv[j], i, 0))
				tmp = argv[j];
		}
		str[i] = ft_strdup(tmp);
	}
	return (str);
}

char	contain_lstent(t_lstent *ref, t_lstent *add)
{
	while (ref)
	{
		if (ref->ent->d_ino == add->ent->d_ino)
			return (1);
		ref = ref->next;
	}
	return (0);
}

t_lstent	*get_next_lstent(t_lstent *lst, t_lstent *out)
{
	t_stat		*buf;
	t_stat		*buf2;
	t_lstent	*add;

	add = NULL;
	while (lst)
	{
		if (!add)
			add = lst;
		else
		{
			stat(lst->ent->d_name, buf);
			stat(add->ent->d_name, buf2);
			if (buf->st_mtime < add->st_mtime && !contain_lstent(out, add))
				add = lst;
			add = lst;
		}
		lst = lst->next;
	}
	return (add);
}

void	add_ascii_time(t_lstent **lst)
{
	t_lstent	*out;
	t_lstent	*begin;
	t_lstent	*tmp;
	t_lstent	*time_span;

	out = NULL;
	while (1)
	{
		tmp = *lst;
		time_span = get_next_lstent(tmp, out);
		if (!out)
		{
			out = tmp2;
			begin = out;
		}
		else
		{
			out->next = tmp2;
			out = out->next;
		}
	}
	free_lstent(lst);
	*lst = out;
}

t_lstent	*sort_time(DIR *dir, char point)
{
	t_lstent	*lst;

	lst = sort_ascii(dir, point);
	lst = sort_lst_time(&lst)
	return (lst);
}