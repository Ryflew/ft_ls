/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 22:47:39 by vdarmaya          #+#    #+#             */
/*   Updated: 2016/12/11 19:04:36 by vdarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <stdlib.h>
# include <dirent.h>
#include <stdio.h>

typedef struct dirent t_dirent;

int		main(int argc, char **argv)
{
	DIR 		*dir;
	t_dirent	*entity;

	dir = NULL;
	entity = NULL;
	argc = 0;
	if (!(dir = opendir(argv[1])))
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	while ((entity = readdir(dir)))
	    printf("nom : |%s| name_len : |%u| num : |%llu|  reclen : |%u| type : |%hhu|\n",
			entity->d_name, entity->d_namlen, entity->d_ino, entity->d_reclen, entity->d_type);
	closedir(dir);
	exit(EXIT_SUCCESS);
}

/* ls sans param affiche par ordre ascii, affiche pas les '.'

-a ajoute tous les fichiers '.', toujour par ordre ascii - Done
-r affiche par ordre ascii inverse
-t affiche par date de modification (du plus recent au plus ancien), puis par ordre ascii si meme date de modification
-l affiche avec les details par ordre ascii
-R recursif - Done

TODO:

le -R pour le dossier courant.

*/