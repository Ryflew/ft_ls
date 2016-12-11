/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrwp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 20:27:30 by vdarmaya          #+#    #+#             */
/*   Updated: 2016/11/29 18:13:36 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstrwp(char *str, int precision)
{
	if ((precision != -1) && ((size_t)precision < ft_strlen(str)))
	{
		while (precision--)
		{
			ft_putchar(*str);
			str++;
		}
	}
	else
		ft_putstr(str);
}
