/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 23:18:42 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/10 16:34:10 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

char	checkminmaj(t_elem *files)
{
	while (files)
	{
		if (S_ISCHR(files->st_mode) || S_ISBLK(files->st_mode))
			return (1);
		files = files->next;
	}
	return (0);
}

void	swap_elem(t_elem **a, t_elem **b)
{
	t_elem	tmp;

	tmp = **a;
	elem_cpy(a, *b);
	elem_cpy(b, &tmp);
}

void	swap_list(t_list **elem1, t_list **elem2)
{
	void	*content;
	size_t	size;

	content = (*elem1)->content;
	size = (*elem1)->content_size;
	(*elem1)->content = (*elem2)->content;
	(*elem1)->content_size = (*elem2)->content_size;
	(*elem2)->content = content;
	(*elem2)->content_size = size;
}

char	check_link(char *path)
{
	struct stat	file;

	if (lstat(path, &file) != -1)
	{
		if (S_ISLNK(file.st_mode))
			return (1);
	}
	else
		opendir(path);
	return (0);
}

char	is_link(char *path, t_opt arg)
{
	struct stat	file;

	if (arg.l == 1)
	{
		if (lstat(path, &file) != -1)
			if (S_ISLNK(file.st_mode))
				return (1);
	}
	return (0);
}
