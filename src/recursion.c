/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 23:18:05 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/07 23:25:54 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void	do_recursion(t_opt arg, char *path)
{
	t_elem	*files;
	DIR		*dir;

	files = NULL;
	ft_putchar('\n');
	ft_putstr(path);
	ft_putstr(":\n");
	if ((dir = opendir(path)) != NULL)
	{
		while (elemget(&files, readdir(dir), \
					ft_strjoin(path, "/"), arg) != 0)
			;
		closedir(dir);
		if (files)
			display_file(arg, files, 1);
		files = NULL;
	}
	else
		basicerror("ft_ls: ", path, 0);
}

void	recursion(t_opt arg, t_elem *files)
{
	t_elem	*cur;

	cur = files;
	while (cur)
	{
		if (cur->name && cur->path && \
				S_ISDIR(cur->st_mode) && \
				ft_strcmp(".", cur->name) && \
				ft_strcmp("..", cur->name) && \
				!(arg.a == 0 && cur->name[0] == '.'))
			do_recursion(arg, cur->path);
		cur = cur->next;
	}
}
