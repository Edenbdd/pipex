/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:42:26 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/19 12:19:37 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Functions to find the path associated with each
// and testing their access

#include "../includes/libft.h"
#include "../includes_bonus/pipex_bonus.h"

char	*handle_cmd(char *cmd, char **env, t_err *err)
{
	char	**paths;
	char	*right_path;

	if (!env)
		return (absolute_path(cmd, err));
	right_path = NULL;
	paths = ft_split(getenv("PATH"), ':');
	if (!paths)
		error_exit(1, 1, error_msg(err, "paths in handle cmd "), err);
	right_path = test_path(paths, cmd, err);
	free(paths);
	if (!right_path)
	{
		right_path = absolute_path(cmd, err);
		if (!right_path)
			error_exit(1, 1, error_msg(err, "no_right found in handle cmd "), err);
	}
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
				error_exit(1, 1, error_msg(err, "cmd "), err);
		}
		triple_free(paths[i], to_test, NULL);
		i++;
	}
	return (right_path);
}

void	triple_free(char *path, char *tmp, char *to_test)
{
	free(path);
	free(tmp);
	free(to_test);
}

char	*absolute_path(char *cmd, t_err *err)
{
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		else
		{
			error_exit(-1, -1, error_msg(err, "cmd "), err);
			return (NULL);
		}
	}
	else
	{
		error_exit(-1, -1, error_msg(err, "cmd "), err);
		return (NULL);
	}
}
