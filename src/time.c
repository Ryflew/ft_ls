/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 23:18:36 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/08 18:10:31 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void	display_date(time_t date)
{
	char	*str1;
	char	*str2;
	char	*tmp;

	str1 = ctime(&date);
	if ((time(0) - 15778463) > date || time(0) < date)
	{
		str2 = ft_strsub(str1, 20, 4);
		str1 = ft_strsub(str1, 4, 6);
		tmp = str1;
		str1 = ft_strjoin(tmp, "  ");
		free(tmp);
		tmp = str1;
		str1 = ft_strjoin(tmp, str2);
		free(str2);
		free(tmp);
	}
	else
		str1 = ft_strsub(str1, 4, 12);
	str1[12] = '\0';
	ft_putstr(str1);
	ft_putchar(' ');
	free(str1);
}
