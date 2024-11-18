/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:48:25 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/18 17:08:24 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 2 functions that each gather all the children specific instructions

#include "../includes_bonus/pipex_bonus.h"
#include "../includes/libft.h"

void	child_process(t_err *err, char *infile, char *outfile, char **env)
{
	char	*path;
	//input redirection
	if (err->cmd_index == 0)
	{
		err->previous_fd = open(infile, O_RDONLY);
		error_exit(err->previous_fd, -1, error_msg(err, "open infile failed "), err);
	}
	dup2(err->previous_fd, STDIN_FILENO);
	close(err->previous_fd);
	// output redirection
	if (err->cmd_index == err->cmd_nb)
	{
		err->fd[1] = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		error_exit(err->fd[1], -1, error_msg(err, "open outfile failed "), err);
	}
	dup2(err->fd[1], STDOUT_FILENO);
	close(err->fd[1]);
	//execution
	path = handle_cmd(err->cmds[err->cmd_index][0], env, err);
	close(err->fd[0]);
	if (execve(path, err->cmds[err->cmd_index], env))
	{
		free(path);
		error_exit(-1, -1, error_msg(err, "exexcve failed "), err);
	}
}

void heredoc_child_process(t_err *err, char *outfile, char **env)
{
    char *path;
    int fd_out;

    if (err->cmd_index == 0)
        dup2(err->previous_fd, STDIN_FILENO);
    else
        dup2(err->fd[0], STDIN_FILENO);
    close(err->previous_fd);
    close(err->fd[0]);
    if (err->cmd_index == 1)
    {
        fd_out = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
        error_exit(fd_out, -1, error_msg(err, "open outfile failed "), err);
        dup2(fd_out, STDOUT_FILENO);
        close(fd_out);
        close(err->fd[1]);
    }
    else
    {
        dup2(err->fd[1], STDOUT_FILENO);
        close(err->fd[1]);
    }
    path = handle_cmd(err->cmds[err->cmd_index][0], env, err);
    if (execve(path, err->cmds[err->cmd_index], env))
    {
        free(path);
        error_exit(-1, -1, error_msg(err, "execve failed "), err);
    }
}