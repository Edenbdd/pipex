/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:42:26 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/20 14:58:00 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Functions to find the path associated with each
// and testing their access

#include "../includes_bonus/pipex_bonus.h"
#include "libft.h"

char	*ft_getenv(char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 5;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			break ;
		i++;
	}
	return (&env[i][j]);
}

char	*handle_cmd(char *cmd, char **env, t_err *err)
{
	char	**paths;
	char	*right_path;

	if (!cmd || !cmd[0])
		error_exit(1, 1, error_msg(err, "empty cmd "), err);
	if (!env || cmd[0] == '.' || cmd[0] == '/')
		return (absolute_path(cmd, err));
	paths = ft_split(ft_getenv(env), ':');
	if (!paths)
		error_exit(1, 1, "paths in handle cmd ", err);
	right_path = test_path(paths, cmd, err);
	free_path(paths);
	if (!right_path)
		error_exit(1, 1, error_msg(err, "cmd path cannot be found "), err);
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
		error_exit(1, 1, error_msg(err, "ft_join failed for tmp "), err);
	}
	to_test = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!to_test)
	{
		free_path(paths);
		error_exit(1, 1, error_msg(err, "ft_join failed for to_test "), err);
	}
	return (to_test);
}

char	*test_path(char **paths, char *cmd, t_err *err)
{
	int		i;
	char	*to_test;
	char	*right_path;

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
		free(to_test);
		i++;
	}
	return (right_path);
}

char	*absolute_path(char *cmd, t_err *err)
{
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		else
		{
			error_exit(1, 1, error_msg(err,
					"absolute/relative path can't be executed "), err);
			return (NULL);
		}
	}
	else
		return (NULL);
}
