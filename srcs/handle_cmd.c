/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:42:26 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/12 15:16:37 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TEST AND VALGRIND THIS THING SEPARATLY TO MAKE SURE JOIN AND SPLIT DONT LEAK

//For now only the handle_cmd command, change this later if needed
// char **env
#include "pipex.h"
#include "libft.h"

//A COUPER EN DEUX OU TROIS POUR REDUIRE LE NOMBRE DE LIGNE
char	*handle_cmd(char *cmd)
{
	char	**paths;
	int		i;
	char	*tmp;
	char	*to_test;
	char	*right_path;

	paths = ft_split(getenv("PATH"), ':');
	i = 0;
	right_path = NULL;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		to_test = ft_strjoin(tmp, cmd);
		if (access(to_test, F_OK) == 0)
		{
			if (access(to_test, X_OK) == 0)
			{
				if (right_path)
					free(right_path);
				right_path = ft_strdup(to_test); // this leaks idk how to solve it
			}
			else
				perror(NULL);
		}
		free(paths[i]);
		free(tmp);
		free(to_test);
		i++;
	}
	free(paths);
	if (!right_path)
	{
		right_path = absolute_path(cmd);
		if (!right_path)
			exit(127);
	}
	return (right_path);
}

char	*absolute_path(char *cmd)
{
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		else
		{
			perror(NULL);
			exit(1);
		}
	}
	else
	{
		perror(NULL);
		exit(1);
	}
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