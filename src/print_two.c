/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 02:22:54 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/09 03:51:19 by vdarmaya         ###   ########.fr       */
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