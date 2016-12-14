/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 21:32:32 by vdarmaya          #+#    #+#             */
/*   Updated: 2016/12/14 16:35:19 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h>
#include "../includes/ft_ls.h"

char	contain(char **s1, char *str, int inc, char opt)
{
	int		i;

	i = 0;
	if (opt)
		i++;
	while (++i < inc)
	{
		if (!ft_strcmp(s1[i], str))
			return (1);
	}
	return (0);
}

char	**argv_opt(int argc, char **argv)
{
	int		i;
	int		j;
	char	**str;
	char	*tmp;

	str = (char**)malloc(sizeof(char*) * (argc + 1));
	str[0] = ft_strdup(argv[0]);
	str[1] = ft_strdup(argv[1]);
	str[argc] = NULL;
	i = 1;
	while (++i < argc)
	{
		j = 1;
		tmp = NULL;
		while (argv[++j])
		{
			if (!tmp && !contain(str, argv[j], i, 1))
				tmp = argv[j];
			else if (tmp && ft_strcmp(tmp, argv[j]) >= 0 && !contain(str, argv[j], i, 1))
				tmp = argv[j];
		}
		str[i] = ft_strdup(tmp);
	}
	return (str);
}

char	get_bigger_argv(char *path, char *add)
{
	t_stat	buff;
	t_stat	buff2;

	if (stat(path, &buff) != -1 && stat(add, &buff2) != -1)
		if (buff.st_mtime > buff2.st_mtime)
			return (1);
	return (0);
}

char	**argv_t(int argc, char **argv)
{
	int		i;
	int		j;
	char	**str;
	char	*tmp;

	str = (char**)malloc(sizeof(char*) * (argc + 1));
	str[0] = ft_strdup(argv[0]);
	str[1] = ft_strdup(argv[1]);
	str[argc] = NULL;
	tmp = NULL;
	i = 1;
	while (++i < argc)
	{
		j = 1;
		tmp = NULL;
		while (argv[++j])
		{
			if (!tmp && !contain(str, argv[j], i, 1))
				tmp = argv[j];
			else if (tmp && !contain(str, argv[j], i, 1) && get_bigger_argv(argv[j], tmp))
				tmp = argv[j];
		}
		str[i] = ft_strdup(tmp);	
	}
	return (str);
}

char	**sort_argv(int argc, char **argv, t_opt *opt)
{
	int		i;
	int		j;
	char	**str;
	char	*tmp;

	if (opt)
		return (opt->set_t ? argv_t(argc, argv) : argv_opt(argc, argv));
	str = (char**)malloc(sizeof(char*) * (argc + 1));
	str[0] = ft_strdup(argv[0]);
	str[argc] = NULL;
	i = 0;
	while (++i < argc)
	{
		j = 0;
		tmp = NULL;
		while (argv[++j])
		{
			if (!tmp && !contain(str, argv[j], i, 0))
				tmp = argv[j];
			else if (tmp && ft_strcmp(tmp, argv[j]) >= 0 && !contain(str, argv[j], i, 0))
				tmp = argv[j];
		}
		str[i] = ft_strdup(tmp);
	}
	return (str);
}
