/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_percent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:42:59 by vdarmaya          #+#    #+#             */
/*   Updated: 2016/12/04 18:55:34 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int		with_width_percent(t_printf *elem)
{
	int count;

	count = elem->width - 1;
	if (elem->flag_minus)
	{
		ft_putchar('%');
		while (count-- > 0)
			ft_putchar(' ');
	}
	else if (elem->flag_zero)
	{
		while (count-- > 0)
			ft_putchar('0');
		ft_putchar('%');
	}
	else
	{
		while (count-- > 0)
			ft_putchar(' ');
		ft_putchar('%');
	}
	return (elem->width);
}

int		ft_percent(t_printf *elem)
{
	int count;

	count = 0;
	if (elem->width)
		count = with_width_percent(elem);
	else
	{
		ft_putchar('%');
		count++;
	}
	return (count);
}
