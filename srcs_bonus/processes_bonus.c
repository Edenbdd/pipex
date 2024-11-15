/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:48:25 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/15 18:13:51 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 2 functions that each gather all the children specific instructions

#include "../includes_bonus/pipex_bonus.h"

void	child_process(t_err *err, char *infile, char *outfile, char **env)
{
	char	*path;

	if (err->cmd_index == 0)
		err->previous_fd[0] = open(infile, O_RDONLY);
	dup2(err->previous_fd[0], STDIN_FILENO);
	close(err->previous_fd[0]);
	if (err->cmd_index == err->cmd_nb)
		err->fd[1] = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	close(err->previous_fd[1]);
	dup2(err->fd[1], STDOUT_FILENO);
	path = handle_cmd(err->cmds[err->cmd_index][0], env, err);
	close(err->fd[0]);
	close(err->fd[1]);
	if (execve(path, err->cmds[err->cmd_index], env))
	{
		free(path);
		error_exit(-1, -1, "first exexcve", err);
	}
}