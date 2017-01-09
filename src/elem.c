/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 23:16:54 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/09 01:56:14 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

t_elem	*elemnew(char *name, char *path, t_opt arg)
{
	t_elem			*elem;
	struct stat		fstat;

	if (!(elem = (t_elem*)malloc(sizeof(t_elem))))
		exit(EXIT_FAILURE);
	elem->name = ft_strdup(name);
	elem->path = ft_strjoin(path, name);
	if (lstat(elem->path, &fstat) == -1)
	{
		basicerror("ft_ls: ", elem->name, 1);
		return (NULL);
	}
	elem->st_mode = fstat.st_mode;
	elem->st_nlink = fstat.st_nlink;
	elem->st_uid = fstat.st_uid;
	elem->st_gid = fstat.st_gid;
	elem->st_size = fstat.st_size;
	elem->st_blocks = fstat.st_blocks;
	elem->date = (arg.u == 1 ? fstat.st_atime : fstat.st_mtime);
	elem->st_rdev = fstat.st_rdev;
	elem->next = NULL;
	return (elem);
}

int		elemget(t_elem **files, struct dirent *file, char *path, t_opt arg)
{
	t_elem	*list;

	list = *files;
	if (!file)
	{
		free(path);
		return (0);
	}
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = elemnew(file->d_name, path, arg);
	}
	else
		*files = elemnew(file->d_name, path, arg);
	free(path);
	return (1);
}

void	elemgetfiles(t_elem **files, char *name, char *path, t_opt arg)
{
	t_elem *list;

	list = *files;
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = elemnew(name, path, arg);
	}
	else
		*files = elemnew(name, path, arg);
}
