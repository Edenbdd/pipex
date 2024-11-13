/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:42:26 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/13 15:21:30 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Functions to find the path associated with each
//and testing their access

#include "pipex.h"
#include "libft.h"

char	*handle_cmd(char *cmd, char **env, t_err *err, char *err_msg)
{
	char	**paths;
	char	*right_path;

	if (!env)
		return (absolute_path(cmd, err, err_msg));
	right_path = NULL;
	paths = ft_split(getenv("PATH"), ':');
	right_path = test_path(paths, cmd, err, err_msg);
	free(paths);
	if (!right_path)
	{
		right_path = absolute_path(cmd, err, err_msg);
		if (!right_path)
			error_exit(1, 1, err_msg, err);
	}
	return (right_path);
}
//diviser en 2 une fois debug fini
char	*test_path(char **paths, char *cmd, t_err *err, char *err_msg)
{
	int		i;
	char	*tmp;
	char	*to_test;
	int		no_permission;
	char	*right_path;

	i = 0;
	no_permission = 0;
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
				right_path = ft_strdup(to_test);
			}
			else
				no_permission++;
		}
		triple_free(paths[i], tmp, to_test);
		i++;
	}
	if (no_permission == 1)
		error_exit(1, 1, err_msg, err);
	return (right_path);
}

void	triple_free(char *path, char *tmp, char *to_test)
{
	free(path);
	free(tmp);
	free(to_test);
}

char	*absolute_path(char *cmd, t_err *err, char *err_msg)
{
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		else
		{
			error_exit(-1, -1, err_msg, err);
			return (NULL);
		}
	}
	else
	{
		error_exit(-1, -1, err_msg, err);
		return (NULL);
	}
}