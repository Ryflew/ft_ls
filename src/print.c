/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 23:17:53 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/10 11:34:22 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"
#include <sys/acl.h>
#include <sys/xattr.h>

void	print_file_type(t_elem *elem)
{
	S_ISFIFO(elem->st_mode) ? ft_putchar('p') : NULL;
	S_ISCHR(elem->st_mode) ? ft_putchar('c') : NULL;
	S_ISDIR(elem->st_mode) ? ft_putchar('d') : NULL;
	S_ISBLK(elem->st_mode) ? ft_putchar('b') : NULL;
	S_ISLNK(elem->st_mode) ? ft_putchar('l') : NULL;
	S_ISSOCK(elem->st_mode) ? ft_putchar('s') : NULL;
	S_ISREG(elem->st_mode) ? ft_putchar('-') : NULL;
}

void	print_access(t_elem *elem)
{
	print_file_type(elem);
	ft_putchar((elem->st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((elem->st_mode & S_IWUSR) ? 'w' : '-');
	if (elem->st_mode & S_ISUID)
		elem->st_mode & S_IXUSR ? ft_putchar('s') : ft_putchar('S');
	else
		ft_putchar((elem->st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((elem->st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((elem->st_mode & S_IWGRP) ? 'w' : '-');
	if (elem->st_mode & S_ISGID)
		elem->st_mode & S_IXGRP ? ft_putchar('s') : ft_putchar('S');
	else
		ft_putchar((elem->st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((elem->st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((elem->st_mode & S_IWOTH) ? 'w' : '-');
	if (elem->st_mode & S_ISVTX)
		(elem->st_mode & S_IXOTH) ? ft_putchar('t') : ft_putchar('T');
	else
		ft_putchar((elem->st_mode & S_IXOTH) ? 'x' : '-');
	if (listxattr(elem->path, NULL, 0, XATTR_NOFOLLOW) > 0)
		ft_putchar('@');
	else
		acl_get_file(elem->path, ACL_TYPE_EXTENDED) != 0 ? ft_putchar('+') : \
			ft_putchar(' ');
	ft_putchar(' ');
}

void	print_int(int nlink, int spacemax)
{
	int		n;
	char	*tmp;

	tmp = ft_itoa(nlink);
	n = spacemax - ft_strlen(tmp);
	free(tmp);
	while (n-- > 0)
		ft_putchar(' ');
	ft_putnbr(nlink);
	ft_putstr(" ");
}

void	print_str(char *str, int spacemax)
{
	int		n;

	n = spacemax - ft_strlen(str);
	ft_putstr(str);
	while (n-- > 0)
		ft_putchar(' ');
	ft_putstr("  ");
}

void	print_majmin(t_elem *file, t_size size)
{
	int		min;
	int		maj;
	char	*tmp;

	tmp = ft_itoa(minor(file->st_rdev));
	min = (int)ft_strlen(tmp);
	free(tmp);
	tmp = ft_itoa(major(file->st_rdev));
	maj = (int)ft_strlen(tmp);
	free(tmp);
	while (maj < size.maj--)
		ft_putchar(' ');
	ft_putnbr(major(file->st_rdev));
	ft_putstr(", ");
	while (min < size.min--)
		ft_putchar(' ');
	ft_putnbr(minor(file->st_rdev));
	ft_putchar(' ');
}
