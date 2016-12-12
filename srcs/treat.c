/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 00:48:28 by vdarmaya          #+#    #+#             */
/*   Updated: 2016/12/12 21:53:06 by vdarmaya         ###   ########.fr       */
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

void	treat_with_opt(int argc, char **argv, t_opt *opt, int inv)
{
	int		i;
	char	multiple;
	int		space;

	i = 1;
	space = (argc - 1) - inv;
	multiple = 0;
	if (argc >= 3)
		multiple = 1;
	while (--argc)
	{
		if (is_valide(argv[++i]))
		{
			if (multiple)
				print_name(argv[i]);
			if (opt->set_rmaj)
				go_recur(ft_strdup(argv[i]), opt, -1);
			else
				treat_current(argv[i], opt);
			if (space-- > 1)
				ft_putchar('\n');
		}
	}
}

void	treat_single_opt(t_opt *opt, int inv)
{
	char	**argv;

	argv = (char**)malloc(sizeof(char*) * 4);
	argv[0] = ft_strdup("");
	argv[1] = ft_strdup("");
	argv[2] = ft_strdup(".");
	argv[3] = NULL;
	treat_with_opt(2, argv, opt, inv);
	ft_strdel(argv);
}