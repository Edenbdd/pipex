/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:42:26 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/19 19:01:56 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Functions to find the path associated with each
// and testing their access

#include "libft.h"
#include "../includes/pipex.h"

char	*ft_getenv(char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 5;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			break;
		i++;
	}
	return (&env[i][j]);
}

char	*handle_cmd(char *cmd, char **env, t_err *err, char *err_msg)
{
	char	**paths;
	char	*right_path;

	if (!env)
	 	return (absolute_path(cmd, err, err_msg, NULL));
	right_path = NULL;
	paths = ft_split(ft_getenv(env), ':');
	if (!paths)
		error_exit(1, 1, "paths in handle cmd :", err);
	right_path = absolute_path(cmd, err, err_msg, paths);
	if (!right_path)
	{
		right_path = test_path(paths, cmd, err, err_msg);
		if (!right_path)
		{
			free_path(paths);
			error_exit(1, 1, err_msg, err);
		}
	}
	free_path(paths);
	return (right_path);
}

char	*join_path(char *path, char *cmd, t_err *err, char **paths)
{
	char	*tmp;
	char	*to_test;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
	{
		free_path(paths);
		error_exit(1, 1, "ft_join failed for tmp :", err);
	}
	to_test = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!to_test)
	{
		free_path(paths);
		error_exit(1, 1, "ft_join failed for to_test :", err);
	}
	return (to_test);
}

char	*test_path(char **paths, char *cmd, t_err *err, char *err_msg)
{
	int		i;
	char	*to_test;
	char	*right_path;
	(void)err_msg;

	i = 0;
	right_path = NULL;
	while (paths[i])
	{
		to_test = join_path(paths[i], cmd, err, paths);
		if (access(to_test, F_OK) == 0)
		{
			if (access(to_test, X_OK) == 0)
			{
				if (right_path)
					free(right_path);
				right_path = ft_strdup(to_test);
			}
			else
				right_path = NULL;
		}
		triple_free(paths[i], to_test, NULL);
		i++;
	}
	return (right_path);
}

char	*absolute_path(char *cmd, t_err *err, char *err_msg, char **path)
{
	(void)err;
	(void)err_msg;
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		else
		{
			if (path)
				free_path(path);
			error_exit(1, 1, err_msg, err);
			return (NULL);
		}
	}
	else
		return (NULL);
}
