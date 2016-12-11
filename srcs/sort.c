/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 20:20:51 by vdarmaya          #+#    #+#             */
/*   Updated: 2016/12/11 18:17:37 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/ft_ls.h"

void	add_ascii(t_lstent **lst, t_lstent *add, char point)
{
	t_lstent	*prev;
	t_lstent	*tmp;

	tmp = *lst;
	prev = tmp;
	while (tmp && (ft_strcmp(tmp->ent->d_name, add->ent->d_name) < 0))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if ((!*lst && point) || (!*lst && add->ent->d_name[0] != '.'))
		*lst = add;
	else if (*lst && (point || prev->ent->d_name[0] != '.'))
	{
		if (ft_strcmp(prev->ent->d_name, add->ent->d_name) >= 0)
		{
			add->next = *lst;
			*lst = add;
			return ;
		}
		add->next = prev->next;
		prev->next = add;
	}
}

t_lstent	*sort_ascii(DIR *dir, char point)
{
	t_lstent	*lst;
	t_lstent	*tmp;
	t_dirent	*entity;

	lst = NULL;
	while ((entity = readdir(dir)))
	{
		tmp = new_lstent(entity);
		add_ascii(&lst, tmp, point);
		if (!lst)
			free(tmp);
	}
	return (lst);
}

/*
**	Créer une liste "lstent" trier en fonction de leurs options
*/


t_lstent	*sort_opt(DIR *dir, t_opt *opt)
{
	if (!opt)
		return (sort_ascii(dir, 0));
	/*else if (opt->set_r)
		return (opt->set_a ? sort_ascii_rev(dir, 1) : sort_ascii_rev(dir, 0));
	else if (opt->set_t)
		return (opt->set_a ? sort_time(dir, 1) : sort_time(dir, 0));
	else */if (opt->set_a)
		return (sort_ascii(dir, 1));
	else
		return (sort_ascii(dir, 0));
}
