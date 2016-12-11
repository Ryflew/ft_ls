/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 03:51:19 by vdarmaya          #+#    #+#             */
/*   Updated: 2016/12/11 18:32:42 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/ft_ls.h"

t_opt	*get_param(char *str)
{
	t_opt	*opt;
	int		i;

	i = -1;
	if (str[++i] != '-' || (str[i] == '-' && str[i + 1] == '\0'))
		return (NULL);
	opt = new_opt();
	while (str[++i])
	{
		if (str[i] == 'a')
			opt->set_a = 1;
		else if (str[i] == 'l')
			opt->set_l = 1;
		else if (str[i] == 'r')
			opt->set_r = 1;
		else if (str[i] == 'R')
			opt->set_rmaj = 1;
		else if (str[i] == 't')
			opt->set_t = 1;
	}
	return (opt);
}

void	go_core(int argc, char **argv)
{
	t_opt	*opt;
	int		i;

	opt = NULL;
	if (argc > 1 && (opt = get_param(argv[1])))
		i = check_dir_validity(1, argc - 1, argv, NULL);
	else	
		i = check_dir_validity(0, argc, argv, NULL);
	if ((argc > 1) && i == (argc - 1))
		return ;
	if (argc == 1)
		treat_current(".", NULL);
	else if (opt)
	{
		if (argc == 2)
			treat_current(".", opt);
		else
			treat_with_opt(argc - 1, argv, opt);
		free(opt);
	}
	else
		treat_normal(argc, argv, i);
}
