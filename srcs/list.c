/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 00:54:15 by vdarmaya          #+#    #+#             */
/*   Updated: 2016/12/11 04:10:23 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/ft_ls.h"

t_opt	*new_opt()
{
	t_opt	*option;

	if (!(option = (t_opt*)malloc(sizeof(t_opt))))
		exit(EXIT_FAILURE);
	option->set_a = 0;
	option->set_l = 0;
	option->set_r = 0;
	option->set_rmaj = 0;
	option->set_t = 0;
	return (option);
}

t_lstent	*new_lstent(t_dirent *entity)
{
	t_lstent	*elem;

	if (!(elem = (t_lstent*)malloc(sizeof(t_lstent))))
		exit(EXIT_FAILURE);
	elem->ent = entity;
	elem->next = NULL;
	return (elem);
}

void	del(void *name, size_t content_size)
{
	free(name);
	(void)content_size;
}

void	free_lstent(t_lstent **lst)
{
	t_lstent	*next;
	t_lstent	*tmp;

	next = *lst;
	while (next)
	{
		tmp = next->next;
		free(next);
		next = tmp;
	}
}
