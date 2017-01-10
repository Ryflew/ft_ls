/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 23:18:13 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/10 11:48:35 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void	get_size_errorhandling(t_size *size, t_elem *cur)
{
	struct passwd	*user;
	struct group	*group;
	char			*tmp;

	tmp = ft_itoa(cur->st_uid);
	if ((user = getpwuid(cur->st_uid)))
		size->userspace = (int)ft_strlen(user->pw_name) > size->userspace ? \
		(int)ft_strlen(user->pw_name) : size->userspace;
	else
		size->userspace = (int)ft_strlen(tmp) > size->userspace ? \
			(int)ft_strlen(tmp) : size->userspace;
	free(tmp);
	tmp = ft_itoa(cur->st_gid);
	if ((group = getgrgid(cur->st_gid)))
		size->groupspace = (int)ft_strlen(group->gr_name) > size->groupspace ? \
			(int)ft_strlen(group->gr_name) : size->groupspace;
	else
		size->groupspace = (int)ft_strlen(tmp) > size->groupspace ? \
			(int)ft_strlen(tmp) : size->groupspace;
	free(tmp);
}

void	get_size_quick(t_size *size, t_elem *cur)
{
	char	*tmp;

	tmp = ft_itoa(cur->st_nlink);
	size->linkspace = (int)ft_strlen(tmp) > size->linkspace ? \
		(int)ft_strlen(tmp) : size->linkspace;
	free(tmp);
	tmp = ft_itoa(major(cur->st_rdev));
	size->maj = (int)ft_strlen(tmp) > size->maj ? \
		(int)ft_strlen(tmp) : size->maj;
	free(tmp);
	tmp = ft_itoa(minor(cur->st_rdev));
	size->min = (int)ft_strlen(tmp) > size->min ? \
		(int)ft_strlen(tmp) : size->min;
	free(tmp);
	tmp = ft_itoa(cur->st_size);
	size->size = (int)ft_strlen(tmp) > size->size ? \
		(int)ft_strlen(tmp) : size->size;
	free(tmp);
	size->total += cur->st_blocks;
}

t_size	get_size(t_opt arg, t_elem *files)
{
	t_elem	*cur;
	t_size	size;

	size = (t_size){0, 0, 0, 0, 0, 0, 0};
	cur = files;
	while (cur)
	{
		if (!(arg.a == 0 && cur->name[0] == '.'))
		{
			get_size_quick(&size, cur);
			get_size_errorhandling(&size, cur);
		}
		cur = cur->next;
	}
	return (size);
}
