/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 23:17:41 by vdarmaya          #+#    #+#             */
/*   Updated: 2017/01/10 16:53:55 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

int		one_of(char c, char *str)
{
	int		i;

	if (str == NULL || c == '\0')
		return (0);
	i = -1;
	while (str[++i])
		if (c == str[i])
			return (1);
	return (0);
}

void	get_arg2(t_opt *arg, char *str, int i)
{
	arg->l = (str[i] == 'l' ? 1 : arg->l);
	arg->upper_r = (str[i] == 'R' ? 1 : arg->upper_r);
	arg->upper_s = (str[i] == 'S' ? 1 : arg->upper_s);
	arg->a = (str[i] == 'a' ? 1 : arg->a);
	arg->r = (str[i] == 'r' ? 1 : arg->r);
	arg->t = (str[i] == 't' ? 1 : arg->t);
	arg->c = (str[i] == 'u' ? 0 : arg->c);
	arg->u = (str[i] == 'u' ? 1 : arg->u);
	arg->f = (str[i] == 'f' ? 1 : arg->f);
	arg->l = (str[i] == 'f' ? 0 : arg->l);
	arg->a = (str[i] == 'f' ? 1 : arg->a);
	arg->g = (str[i] == 'g' ? 1 : arg->g);
	arg->g = (str[i] == '1' ? 0 : arg->g);
	arg->l = (arg->g == 1 ? 0 : arg->l);
	arg->l = (str[i] == '1' ? 0 : arg->l);
	arg->u = ((arg->u == 1 && str[i] == 'c') ? 0 : arg->u);
	arg->c = (str[i] == 'c' ? 1 : arg->c);
}

void	get_arg(t_opt *arg, char *str, char *end)
{
	int		i;

	i = 0;
	while (str[++i])
	{
		if (str[1] == '-')
			*end = 1;
		if (one_of(str[i], "1lRSafgrtuc") || (str[1] == '-' && !str[2]))
			get_arg2(arg, str, i);
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
		if (!end && param[i] && param[i][0] == '-' && param[i][1])
			get_arg(arg, param[i], &end);
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

	arg = (t_opt){0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	path = NULL;
	if (argc > 1)
		get_param(argc - 1, argv, &arg, &path);
	if (path == NULL)
		path = ft_lstnew(".", 1);
	sort_argv(&path);
	core(arg, path, path->next != NULL ? 1 : 0, NULL);
	free_list(&path);
	return (0);
}
