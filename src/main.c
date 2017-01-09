/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 23:17:41 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/09 04:17:15 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

char	contain(char **s1, char *str, int inc)
{
	int		i;

	i = 0;
	while (++i < inc)
	{
		if (!ft_strcmp(s1[i], str))
			return (1);
	}
	return (0);
}

char	**sort_argv(int argc, char **argv)
{
	int		i;
	int		j;
	char	**str;
	char	*tmp;

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
			if (!tmp && !contain(str, argv[j], i))
				tmp = argv[j];
			else if (tmp && ft_strcmp(tmp, argv[j]) >= 0 && \
					!contain(str, argv[j], i))
				tmp = argv[j];
		}
		str[i] = ft_strdup(tmp);
	}
	return (str);
}

void	get_arg(t_opt *arg, char *str)
{
	int		i;

	i = 0;
	while (str[++i])
	{
		if (one_of(str[i], "1lRafgrtu") || (str[1] == '-' && !str[2]))
		{
			arg->l = (str[i] == 'l' ? 1 : arg->l);
			arg->upper_r = (str[i] == 'R' ? 1 : arg->upper_r);
			arg->a = (str[i] == 'a' ? 1 : arg->a);
			arg->r = (str[i] == 'r' ? 1 : arg->r);
			arg->t = (str[i] == 't' ? 1 : arg->t);
			arg->u = (str[i] == 'u' ? 1 : arg->u);
			arg->f = (str[i] == 'f' ? 1 : arg->f);
			arg->l = (str[i] == 'f' ? 0 : arg->l);
			arg->a = (str[i] == 'f' ? 1 : arg->a);
			arg->g = (str[i] == 'g' ? 1 : arg->g);
			arg->l = (str[i] == '1' ? 0 : arg->l);
		}
		else
			error_arg(str[i]);
	}
}

void	get_param(int nb, char **param, t_opt *arg, t_list **path)
{
	int		i;
	char	end;

	i = 0;
	end = 0;
	while (++i <= nb)
	{
		if (!end && param[i] && param[i][0] == '-')
			get_arg(arg, param[i]);
		else
		{
			ft_lstaddend(path, param[i], ft_strlen(param[i]));
			end = 1;
		}
	}
}

int		main(int argc, char **argv)
{
	t_opt	arg;
	t_list	*path;
	char	**new_argv;

	new_argv = sort_argv(argc, argv);
	arg = (t_opt){0, 0, 0, 0, 0, 0, 0, 0};
	path = NULL;
	if (argc > 1)
		get_param(argc - 1, new_argv, &arg, &path);
	if (path == NULL)
		path = ft_lstnew(".", 1);
	core(arg, path, path->next != NULL ? 1 : 0, NULL);
	free_list(&path);
	free_argv(&new_argv);
	return (0);
}

/*
**
** TODO :
** Bug src include
** Gérer le ~ pour le transformer en home et fix le bug /Users/vdarmaya
**
*/
