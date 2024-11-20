/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:54:10 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/20 10:14:48 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Functions to free, close and clean up

#include "../includes_bonus/pipex_bonus.h"

void	closing(t_err *err)
{
	if (err->fd[1] != -1)
		close(err->fd[1]);
	if (err->fd[0] != -1)
		close(err->fd[0]);
	if (err->previous_fd != -1)
		close(err->previous_fd);
}

void	triple_free(char *tmp, char *to_test)
{
	free(tmp);
	free(to_test);
}

void	free_close(t_err *err)
{
	closing(err);
	if (!access("heredoc_tmp", F_OK))
	{
		if (unlink("heredoc_tmp") == -1)
			perror("heredoc_tmp unlink error : ");
	}
	free_cmds(err);
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