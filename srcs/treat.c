/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 00:48:28 by vdarmaya          #+#    #+#             */
/*   Updated: 2016/12/11 19:15:52 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/ft_ls.h"

/*
**	Affiche le contenu d'un dir en fonction de opt, si opt = NULL alors la
**	sortie sera par ordre ASCII.
*/

void	treat_current(char *str, t_opt *opt)
{
	DIR			*dir;
	t_lstent	*lst;

	dir = opendir(str);
	lst = sort_opt(dir, opt);
	closedir(dir);
	print_normal(lst);
	if (lst)
		free_lstent(&lst);
}

/*
**	Traite tous les dossiers passé en paramètre sans les options. 
*/

void	treat_normal(int argc, char **argv, int invalid)
{
	DIR		*dir;
	int		i;
	int		space;

	i = 0;
	space = (argc - 1) - invalid;
	if (argc == 2)
	{
		treat_current(argv[1], NULL);
		return ;
	}
	while (--argc)
	{
		if ((dir = opendir(argv[++i])))
		{
			closedir(dir);
			print_name(argv[i]);
			treat_current(argv[i], NULL);
			if ((space-- > 1))
				ft_putchar('\n');
		}
	}
}

/*
**	Traite tous les dossiers passé en paramètre avec les options. 
*/

void	treat_with_opt(int argc, char **argv, t_opt *opt)
{
	int		i;
	char	multiple;

	i = 1;
	multiple = 0;
	if (argc >= 3)
		multiple = 1;
	while (--argc)
	{
		if (is_valide(argv[++i]))
		{
			if (i > 2)
				ft_putchar('\n');
			if (multiple)
				print_name(argv[i]);
			if (opt->set_rmaj)
				go_recur(argv[i], opt);
			else
				treat_current(argv[i], opt);
		}
	}
}
