/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 22:47:39 by vdarmaya          #+#    #+#             */
/*   Updated: 2016/12/12 23:49:34 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
# include <dirent.h>
#include <stdio.h>

typedef struct dirent t_dirent;
typedef struct stat t_stat;

int		main(int argc, char **argv)
{
	DIR 		*dir;
	t_dirent	*entity;
	t_stat		donnee;

	dir = NULL;
	entity = NULL;
	argc = 0;
	if (!(dir = opendir(argv[1])))
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	while ((entity = readdir(dir)))
	{
	    printf("nom : |%s| name_len : |%u| num : |%llu|  reclen : |%u| type : |%hhu| time : |%ld|\n",
			entity->d_name, entity->d_namlen, entity->d_ino, entity->d_reclen, entity->d_type, donnee.st_mtime);
		if (stat(entity->d_name, &donnee) == -1)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
	}
	closedir(dir);
	exit(EXIT_SUCCESS);
}

/* ls sans param affiche par ordre ascii, affiche pas les '.'

-a ajoute tous les fichiers '.', toujour par ordre ascii - Done
-r affiche par ordre ascii inverse - Done
-t affiche par date de modification (du plus recent au plus ancien), puis par ordre ascii si meme date de modification
-l affiche avec les details par ordre ascii
-R recursif - Done

TODO:

Les erreurs sytle Permission denied etc..

*/