/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 00:38:13 by vdarmaya          #+#    #+#             */
/*   Updated: 2016/12/11 19:17:09 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/ft_ls.h"

void	invalid(char c)
{
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putchar_fd('\n', 2);
	ft_putendl_fd("usage: ./ft_ls [-alRrt] [file ...]", 2);
	exit(EXIT_SUCCESS);
}

void	add_pos(t_list **entity, t_list *add, char *str)
{
	t_list	*prev;
	t_list	*tmp;

	tmp = *entity;
	prev = tmp;
	while (tmp)
	{
		if (ft_strcmp(tmp->content, str) >= 0)
			break ;
		prev = tmp;
		tmp = tmp->next;
	}
	if (!*entity)
		*entity = add;
	else
	{
		if (ft_strcmp(prev->content, str) >= 0)
		{
			add->next = *entity;
			*entity = add;
			return ;
		}
		add->next = prev->next;
		prev->next = add;
	}
}

int		check_dir_validity(int i, int argc, char **argv, t_list	*entity)
{
	DIR		*dir;
	t_list	*tmp;
	int		inv;

	inv = 0;
	while (--argc > 0)
	{
		if (!(dir = opendir(argv[++i])))
		{
			tmp = ft_lstnew(argv[i], ft_strlen(argv[i]) + 1);
			add_pos(&entity, tmp, argv[i]);
			inv++;
		}
		else
			closedir(dir);
	}
	tmp = entity;
	while (tmp)
	{
		print_invalid(tmp->content);
		perror("");
		tmp = tmp->next;
	}
	ft_lstdel(&entity, del);
	return (inv);
}

char	is_valide(char *path)
{
	DIR 		*dir;

	if (!(dir = opendir(path)))
		return (0);
	closedir(dir);
	return (1);
}