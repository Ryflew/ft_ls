/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_opt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 17:55:10 by vdarmaya          #+#    #+#             */
/*   Updated: 2016/12/14 00:15:05 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h>
#include <stdlib.h>
#include "../includes/ft_ls.h"

void	del_in_lst(t_lstent **lst, t_lstent *add)
{
	t_lstent	*begin;
	t_lstent	*prev;

	begin = *lst;
	prev = begin;
	if ((*lst)->ent->d_ino == add->ent->d_ino)
	{
		*lst = (*lst)->next;;
		return ;
	}
	while (*lst)
	{
		if ((*lst)->ent->d_ino == add->ent->d_ino)
		{
			prev->next = (*lst)->next;
			*lst = begin;
			return ;
		}
		prev = *lst;
		*lst = (*lst)->next;
	}
}

void	add_if_bigger(t_lstent **add, t_lstent *tmp, char *path)
{
	t_stat		buf;
	t_stat		buf2;
	char	*s1;
	char	*s2;

	s1 = ft_strjoin_sep(path, "/", tmp->ent->d_name);
	s2 = ft_strjoin_sep(path, "/", (*add)->ent->d_name);	
	if (stat(s1, &buf) != -1 && stat(s2, &buf2) !=-1)
		if (buf.st_mtime > buf2.st_mtime)
			*add = tmp;
	free(s1);
	free(s2);
}

t_lstent	*get_next_lstent(t_lstent **lst, char*path)
{
	t_lstent	*add;
	t_lstent	*tmp;

	tmp = *lst;
	add = NULL;
	while (tmp)
	{
		if (!add)
			add = tmp;
		else
			add_if_bigger(&add, tmp, path);
		tmp = tmp->next;
	}
	del_in_lst(lst, add);
	return (add);
}

void	sort_lstent_time(t_lstent **lst, char *path)
{
	t_lstent	*out;
	t_lstent	*tmp;
	t_lstent	*begin;

	out = NULL;
	while (*lst)
	{
		tmp = get_next_lstent(lst, path);
		tmp->next = NULL;
		if (!out)
		{
			out = tmp;
			begin = out;
		}
		else
		{
			out->next = tmp;
			out = out->next;
		}
	}
	*lst = begin;
}

t_lstent	*sort_time(DIR *dir, char point, char *path)
{
	t_lstent	*lst;

	lst = sort_ascii(dir, point);
	sort_lstent_time(&lst, path);
	return (lst);
}
