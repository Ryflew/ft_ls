/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 23:18:13 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/07 23:25:57 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void	get_size_errorhandling(t_size *size, t_elem *cur)
{
	if (getpwuid(cur->st_uid))
		size->userspace = (int)ft_strlen(getpwuid(cur->st_uid)->pw_name) \
			> size->userspace ? (int)ft_strlen(getpwuid(cur->st_uid)->pw_name) \
			: size->userspace;
	else
		size->userspace = (int)ft_strlen(ft_itoa(cur->st_uid)) \
			> size->userspace ? (int)ft_strlen(ft_itoa(cur->st_uid)) \
			: size->userspace;
	if (getgrgid(cur->st_gid))
		size->groupspace = (int)ft_strlen(getgrgid(cur->st_gid)->gr_name) \
			> size->groupspace ? \
			(int)ft_strlen(getgrgid(cur->st_gid)->gr_name) : size->groupspace;
	else
		size->groupspace = (int)ft_strlen(ft_itoa(cur->st_gid)) \
			> size->groupspace ? (int)ft_strlen(ft_itoa(cur->st_gid)) \
			: size->groupspace;
}

void	get_size_quick(t_size *size, t_elem *cur)
{
	size->linkspace = (int)ft_strlen(ft_itoa(cur->st_nlink)) > \
		size->linkspace ? (int)ft_strlen(ft_itoa(cur->st_nlink)) \
		: size->linkspace;
	size->maj = (int)ft_strlen(ft_itoa(major(cur->st_rdev))) > size->maj \
		? (int)ft_strlen(ft_itoa(major(cur->st_rdev))) : size->maj;
	size->min = (int)ft_strlen(ft_itoa(minor(cur->st_rdev))) > size->min ? \
		(int)ft_strlen(ft_itoa(minor(cur->st_rdev))) : size->min;
	size->size = (int)ft_strlen(ft_itoa(cur->st_size)) > size->size ? \
		(int)ft_strlen(ft_itoa(cur->st_size)) : size->size;
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
