/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:48:25 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/19 16:40:20 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 2 functions that each gather all the children specific instructions

#include "../includes/pipex.h"

void	first_child(t_err *err, char *infile, char **env)
{
	char	*path;
	int		in_fd;

	in_fd = open(infile, O_RDONLY);
	error_exit(in_fd, -1, "open infile : ", err);
	dup2(in_fd, STDIN_FILENO);
	close(in_fd);
	dup2(err->fd[1], STDOUT_FILENO);
	path = handle_cmd(err->cmds[0][0], env, err, "first cmd : ");
	close(err->fd[0]);
	close(err->fd[1]);
	if (execve(path, err->cmds[0], env))
	{
		free(path);
		error_exit(-1, -1, "first exexcve : ", err);
	}
}

void	sec_child(t_err *err, char *outfile, char **env)
{
	char	*path;
	int		out_fd;

	dup2(err->fd[0], STDIN_FILENO);
	out_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	error_exit(out_fd, -1, "open outfile : ", err);
	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
	path = handle_cmd(err->cmds[1][0], env, err, "second cmd : ");
	close(err->fd[1]);
	close(err->fd[0]);
	if (execve(path, err->cmds[1], env))
	{
		free(path);
		error_exit(-1, -1, "second exexcve : ", err);
	}
}
