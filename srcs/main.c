/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 03:09:48 by vdarmaya          #+#    #+#             */
/*   Updated: 2016/12/11 18:00:07 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../includes/ft_ls.h"

char	check_param(char *str)
{
	if (!*str || *str != '-' || !((*str) + 1))
		return (0);
	str++;
	while (*str == 'a' || *str == 'l' || *str == 'R' || *str == 'r' ||
		*str == 't')
		str++;
	if (*str != '\0' && (*str != 'a' && *str != 'l' && *str != 'R' &&
		*str != 'r' && *str != 't'))
		return (*str);
	return (0);
}

int		main(int argc, char **argv)
{
	char	ill;

	if ((argc >= 2) && (ill = check_param(argv[1])))
		invalid(ill);
	go_core(argc, argv);
	// sleep(100);
	exit(EXIT_SUCCESS);
}
