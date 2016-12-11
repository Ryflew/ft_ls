/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rmaj_opt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 01:17:51 by vdarmaya          #+#    #+#             */
/*   Updated: 2016/12/11 17:51:09 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/ft_ls.h"

/*
**	Cherche et renvoie le nom du premier dossier ('.' ou non) qu'il rencontre,
**	sauf les deux premiers '.' et "..".
*/

char	*ft_dirchr(t_lstent **lst, t_opt *opt)
{
	char	*str;

	while (*lst)
	{
		if ((*lst)->ent->d_type == 4 && (opt->set_a ||
			(*lst)->ent->d_name[0] != '.') && (!((*lst)->ent->d_namlen == 1 &&
			(*lst)->ent->d_name[0] == '.') && !((*lst)->ent->d_namlen == 2 &&
			!ft_strcmp((*lst)->ent->d_name, ".."))))
			{
				str = (*lst)->ent->d_name;
				*lst = (*lst)->next;
				return (str);
			}
		*lst = (*lst)->next;
	}
	return (NULL);
}

/*
**	Fonction récursive qui parcourt tous les dossiers et affiche leurs infos.
*/

void	go_recur(char *path, t_opt *opt)
{
	DIR			*dir;
	t_lstent	*lst;
	char		*str;
	char		*tmp;

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
	while ((str = ft_dirchr(&lst, opt)))
	{
		tmp = path;
		path = ft_strjoin_sep(path, "/", str);
		go_recur(path, opt);
		free(path);
		path = tmp;
	}
	free_lstent(&lst);
}
