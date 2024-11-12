/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:42:26 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/12 12:59:07 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TEST AND VALGRIND THIS THING SEPARATLY TO MAKE SURE JOIN AND SPLIT DONT LEAK

//For now only the handle_cmd command, change this later if needed
// char **env
#include "../includes/pipex.h"
#include "../includes/libft.h"

//A COUPER EN DEUX OU TROIS POUR REDUIRE LE NOMBRE DE LIGNE
char	*handle_cmd(char *cmd)
{
	char	**paths;
	int		i;
	char	*tmp;
	char	*to_test;
	char	*right_path;

	paths = ft_split(getenv("PATH"), ':');
	if (!paths)
	{
		perror("ft_split failed in handle_cmd\n");
	}
	i = 0;
	right_path = NULL;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		to_test = ft_strjoin(tmp, cmd);
		if (access(to_test, F_OK) == 0)
		{
			//! avec ce fonctionnement, on return la derniere commande qui fonctionne
			//contrairement au shell qui return la premiere, jsp si c est important ??
			if (access(to_test, X_OK) == 0)
			{
				if (right_path)
					free(right_path);
				right_path = ft_strdup(to_test); // this leaks idk how to solve it
			}
			else
				perror("Permission error\n");
			//errror handling to change in case two file exists
			//and only one can be executed 
		}
		free(paths[i]);
		free(tmp);
		free(to_test);
		i++;
	}
	free(paths);
	if (!right_path)
	{
		perror("Command doesn't exists\n");
		return (NULL);
	}
	return (right_path);
}
/* main si besoin de test separement handle_cmd
int	main(void)
{
	char	*path;

	path = handle_cmd("ls");
	printf("right path is: %s\n", path);
	free(path);
	return (0);
}
*/