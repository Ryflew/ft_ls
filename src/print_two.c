/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 02:22:54 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/10 16:49:23 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void	print_link(t_elem *cur)
{
	char	buf[256];

	ft_bzero(buf, 256);
	ft_putstr(" -> ");
	readlink(cur->path, buf, 256);
	ft_putendl(buf);
}

void	print_minmaj_space(t_size size)
{
	int	total;

	total = size.min + size.maj + 1;
	while (total-- > 0)
		ft_putchar(' ');
}

void	display_file(t_opt arg, t_elem *files, int fileordir)
{
	t_elem	*cur;

	cur = files;
	cur = sort_elem(cur, arg);
	(arg.l == 1 || arg.g == 1) ? \
			ls_long(arg, cur, fileordir) : ls_simple(arg, cur);
	arg.upper_r == 1 ? recursion(arg, cur) : NULL;
}
