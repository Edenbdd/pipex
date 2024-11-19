/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:23:17 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/19 18:52:05 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// functions to handle exit codes, errors, no env...etc
// and exit without leaks, includes functions to free specific data structure
//(char ** or char ***) and to free the err struct

#include "../includes/pipex.h"
#include "libft.h"

void	error_exit(int result, int error_return, char *error_msg, t_err *err)
{
	if (result == error_return)
	{
		ft_putstr_fd(error_msg, 2);
		if (errno != 0)
			perror(NULL);
		else
			ft_putstr_fd("\n", 2);
		free_close(err);
		exit(1);
	}
	else
		return ;
}

void	free_close(t_err *err)
{
	if (err->fd)
	{
		if (err->fd[1])
			close(err->fd[1]);
		if (err->fd[0])
			close(err->fd[0]);
		free(err->fd);
	}
	free_cmds(err);
	free(err);
}

void	free_cmds(t_err *err)
{
	int	i;
	int	j;

	i = 0;
	if (err->cmds)
	{
		while (err->cmds[i])
		{
			j = 0;
			while (err->cmds[i][j])
			{
				free(err->cmds[i][j]);
				j++;
			}
			free(err->cmds[i]);
			i++;
		}
		free(err->cmds);
	}
}

void	free_path(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

void	triple_free(char *path, char *tmp, char *to_test)
{
	(void)path;
	// free(path);
	free(tmp);
	free(to_test);
}
