/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:48:25 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/15 10:33:14 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 2 functions that each gather all the children specific instructions

#include "../includes_bonus/pipex_bonus.h"

void	first_child(t_err *err, char *infile, char **env)
{
	char	*path;
	int		in_fd;

	in_fd = open(infile, O_RDONLY);
	error_exit(in_fd, -1, error_msg(err, "open infile failed "), err);
	dup2(in_fd, STDIN_FILENO);
	close(in_fd);
	dup2(err->fd[1], STDOUT_FILENO);
	path = handle_cmd(err->cmds[0][0], env, err);
	close(err->fd[0]);
	close(err->fd[1]);
	if (execve(path, err->cmds[0], env))
	{
		free(path);
		error_exit(-1, -1, error_msg(err, "first execve "), err);
	}
}

void	middle_child(t_err *err, char *outfile, char **env, int cmd_nb)
{
	char	*path;
	char	*msg;
	
	dup2(err->fd[0], STDIN_FILENO);
	close(err->fd[0]);
	dup2(err->fd[1], STDOUT_FILENO);
	close(err->fd[1]);
	msg = error_msg(err, "child ");
	path = handle_cmd(err->cmds[cmd_nb -2][0], env, err);
	free(msg);
	if (execve(path, err->cmds[cmd_nb - 2], env))
	{
		free(path);
		error_exit(-1, -1, error_msg(err, "execve failed "), err);	
	}
}

void	last_child(t_err *err, char *outfile, char **env)
{
	char	*path;
	int		out_fd;

	dup2(err->fd[0], STDIN_FILENO);
	//here_doc modification a faire pour le troncate (remplace by append)
	out_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	error_exit(out_fd, -1, error_msg(err, "last open outfile failed"), err);
	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
	path = handle_cmd(err->cmds[1][0], env, err);
	close(err->fd[1]);
	close(err->fd[0]);
	if (execve(path, err->cmds[1], env))
	{
		free(path);
		error_exit(-1, -1, error_msg(err, "last execve failed"), err);
	}
}
