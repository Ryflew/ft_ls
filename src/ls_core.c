/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 23:17:35 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/10 16:49:19 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void	do_ls_dir2(t_opt arg, t_elem *dirlist, int multidir)
{
	DIR		*dir;
	t_elem	*files;
	int		first;

	first = 0;
	files = NULL;
	while (dirlist)
	{
		dir = opendir(dirlist->name);
		while (elemget(&files, readdir(dir), \
			ft_strjoin(dirlist->path, "/"), arg) != 0)
			;
		closedir(dir);
		if (files)
		{
			first == 1 ? ft_putchar('\n') : NULL;
			multidir ? ft_putstr(dirlist->name) : NULL;
			multidir ? ft_putendl(":") : NULL;
			first = 1;
			display_file(arg, files, 1);
		}
		free_elem(&files);
		files = NULL;
		dirlist = dirlist->next;
	}
}

void	do_ls_dir(t_opt arg, t_list *path, int multidir)
{
	t_list	*cur;
	t_elem	*dirlist;

	cur = path;
	dirlist = NULL;
	while (cur)
	{
		elemgetfiles(&dirlist, cur->content, "", arg);
		cur = cur->next;
	}
	dirlist = sort_elem(dirlist, arg);
	do_ls_dir2(arg, dirlist, multidir);
	free_elem(&dirlist);
}

void	do_ls_file(t_opt arg, t_list *path)
{
	t_list	*cur;
	t_elem	*files;

	cur = path;
	files = NULL;
	arg.a = 1;
	while (cur)
	{
		elemgetfiles(&files, cur->content, "", arg);
		cur = cur->next;
	}
	if (files)
		display_file(arg, files, 0);
	free_elem(&files);
}

void	process(t_list **file, t_list **directory, t_opt arg, int multidir)
{
	*file ? do_ls_file(arg, *file) : NULL;
	*file && *directory ? ft_putchar('\n') : NULL;
	*directory ? do_ls_dir(arg, *directory, multidir) : NULL;
	free_list(file);
	free_list(directory);
}

void	core(t_opt arg, t_list *path, int multidir, t_list *file)
{
	DIR		*dir;
	t_list	*directory;
	t_list	*cur;

	directory = NULL;
	cur = path;
	while (cur)
	{
		if (is_link(cur->content, arg) || (dir = opendir(cur->content)) == NULL)
		{
			if (check_link(cur->content))
				ft_lstaddend(&file, cur->content, cur->content_size);
			else
				errno != ENOTDIR ? basicerror("ft_ls: ", cur->content, 0) : \
					ft_lstaddend(&file, cur->content, cur->content_size);
		}
		else
		{
			ft_lstaddend(&directory, cur->content, cur->content_size);
			if (closedir(dir) == -1)
				basicerror("ft_ls: ", cur->content, 0);
		}
		cur = cur->next;
	}
	process(&file, &directory, arg, multidir);
}
