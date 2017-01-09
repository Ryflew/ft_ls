/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 23:16:40 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/09 03:51:00 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void	ft_color(mode_t mode)
{
	S_ISBLK(mode) ? ft_putstr(C_CYAN) : NULL;
	S_ISCHR(mode) ? ft_putstr(C_BLUE) : NULL;
	S_ISDIR(mode) ? ft_putstr(C_RESET) : NULL;
	S_ISFIFO(mode) ? ft_putstr(C_BROWN) : NULL;
	S_ISREG(mode) ? ft_putstr(C_RESET) : NULL;
	S_ISLNK(mode) ? ft_putstr(C_MAGENTA) : NULL;
	S_ISSOCK(mode) ? ft_putstr(C_GREEN) : NULL;
	if (S_ISREG(mode) && ((mode & S_IXUSR) || (mode & S_IXGRP) ||
		(mode & S_IXOTH)))
		ft_putstr(C_RED);
}

void	ls_simple(t_opt arg, t_elem *files)
{
	t_elem	*cur;

	cur = files;
	while (cur)
	{
		if (!(arg.a == 0 && cur->name[0] == '.'))
		{
			ft_color(cur->st_mode);
			ft_putendl(cur->name);
			ft_putstr(C_RESET);
		}
		cur = cur->next;
	}
}

void	ls_long_file2(t_elem *cur)
{
	display_date(cur->date);
	ft_color(cur->st_mode);
	ft_putstr(cur->name);
	ft_putstr(C_RESET);
	if (S_ISLNK(cur->st_mode))
		print_link(cur);
	else
		ft_putchar('\n');
}

void	ls_long_file(t_opt arg, t_elem *cur, t_size size, char hasminmaj)
{
	char	*tmp;

	print_access(cur);
	print_int(cur->st_nlink, size.linkspace);
	if (arg.g == 0)
	{
		tmp = ft_itoa(cur->st_uid);
		if (getpwuid(cur->st_uid))
			print_str(getpwuid(cur->st_uid)->pw_name, size.userspace);
		else
			print_str(tmp, size.userspace);
		free(tmp);
	}
	tmp = ft_itoa(cur->st_gid);
	if (getgrgid(cur->st_gid))
		print_str(getgrgid(cur->st_gid)->gr_name, size.groupspace);
	else
		print_str(tmp, size.groupspace);
	free(tmp);
	if (S_ISCHR(cur->st_mode) || S_ISBLK(cur->st_mode))
		print_majmin(cur, size);
	else
	{
		if (hasminmaj)
			print_minmaj_space(size);
		print_int(cur->st_size, size.size);
	}
	ls_long_file2(cur);
}

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

void	ls_long(t_opt arg, t_elem *files, int fileordir)
{
	t_elem	*cur;
	t_size	size;
	char	hasminmaj;

	cur = files;
	size = get_size(arg, files);
	hasminmaj = 0;
	if (checkminmaj(cur))
		hasminmaj = 1;
	if (fileordir)
	{
		ft_putstr("total ");
		ft_putnbr(size.total);
		ft_putchar('\n');
	}
	while (cur)
	{
		if (!(arg.a == 0 && cur->name[0] == '.'))
			ls_long_file(arg, cur, size, hasminmaj);
		cur = cur->next;
	}
}
