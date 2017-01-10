/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 23:18:30 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/09 16:56:09 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

int		cmp_alpha(t_elem *elem1, t_elem *elem2)
{
	return (ft_strcmp(elem1->name, elem2->name));
}

int		cmp_time(t_elem *elem1, t_elem *elem2)
{
	return (elem1->date < elem2->date);
}

int		cmp_size(t_elem *elem1, t_elem *elem2)
{
	return (elem1->st_size < elem2->st_size);
}
