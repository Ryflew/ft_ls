/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rmaj_opt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 00:48:28 by vdarmaya          #+#    #+#             */
/*   Updated: 2016/12/12 03:11:29 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/ft_ls.h"
#include "../libft/include/ft_printf.h"

size_t	count_dir(t_lstent **lst)
{
	t_lstent	*tmp;
	size_t		i;

	i = 0;
	tmp = *lst;
	while (tmp)
	{
		if ((tmp->ent->d_type == 4) && ft_strcmp(tmp->ent->d_name, ".") &&
			ft_strcmp(tmp->ent->d_name, ".."))
			i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**get_dir(t_lstent **lst)
{
	t_lstent	*tmp;
	char		**names;
	int			i;

	tmp = *lst;
	if (!tmp)
		return (NULL);
	i = count_dir(lst);
	names = (char**)malloc(sizeof(char*) * (i + 1));
	names[i] = NULL;
	i = -1;
	while (tmp)
	{
		if ((tmp->ent->d_type == 4) && ft_strcmp(tmp->ent->d_name, ".") &&
			ft_strcmp(tmp->ent->d_name, ".."))
			names[++i] = ft_strdup(tmp->ent->d_name);
		tmp = tmp->next;
	}
	free_lstent(lst);	
	return (names);
}

/*
**	Fonction récursive qui parcourt tous les dossiers et affiche leurs infos.
*/

void	go_recur(char *path, t_opt *opt, int i)
{
	DIR			*dir;
	t_lstent	*lst;
	char		**names;

	if (ft_strchr(path, '/'))
	{
		ft_putchar('\n');
		print_name(path);
	}
	if (!(dir = opendir(path)))
		exit(EXIT_FAILURE);
	lst = sort_opt(dir, opt);
	closedir(dir);
	print_normal(lst);
	names = get_dir(&lst);
	while (names && names[++i])
		go_recur(ft_strjoin_sep(path, "/", names[i]), opt, -1);
	free(path);
	if (names)
		ft_strdel(names);
}
