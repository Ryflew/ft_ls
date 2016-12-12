/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 03:51:19 by vdarmaya          #+#    #+#             */
/*   Updated: 2016/12/12 21:40:06 by vdarmaya         ###   ########.fr       */
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
	char	**new_argv;
	int		i;

	opt = NULL;
	if (argc > 1 && (opt = get_param(argv[1])))
		i = check_dir_validity(1, argc - 1, argv, NULL);
	else	
		i = check_dir_validity(0, argc, argv, NULL);
	if ((argc > 1) && i == (argc - 1))
		return ;
	new_argv = sort_argv(argc, argv, opt);
	if (argc == 1)
		treat_current(".", NULL);
	else if (opt)
	{
		if (argc == 2)
			treat_single_opt(opt, i);
		else
			treat_with_opt(argc - 1, new_argv, opt, i);
		free(opt);
	}
	else
		treat_normal(argc, new_argv, i);
	ft_strdel(new_argv);
}
