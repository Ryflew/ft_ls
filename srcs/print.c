/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 20:14:08 by vdarmaya          #+#    #+#             */
/*   Updated: 2016/12/11 17:02:27 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	print_name(char *str)
{
	ft_putstr(str);
	ft_putendl(":");
}

void	print_normal(t_lstent *lst)
{
	while (lst)
	{
		ft_putendl(lst->ent->d_name);
		lst = lst->next;
	}
}

void	print_invalid(char *str)
{
	ft_putstr_fd("ft_ls: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
}

// void	print_l(t_lstent *lst)
// {

// }