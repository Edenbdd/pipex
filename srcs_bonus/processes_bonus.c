/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:48:25 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/19 12:38:51 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Creating and executing children

#include "../includes_bonus/pipex_bonus.h"
#include "../includes/libft.h"

int	children_generator(char **argv, char **env, int argc, t_err *err)
{
	int	i;
	int	id;
	int	stop;

	if (err->heredoc)
		stop = argc - 3;
	else
		stop = argc - 2;
	i = 2;
	while (i <= stop)
	{
		error_exit(pipe(err->fd), -1, error_msg(err, "pipe failed "), err);
		id = fork();
		error_exit(id, -1, error_msg(err, "fork failed "), err);
		if (id == 0)
			child_process(err, argv[1], argv[argc - 1], env);
		err->cmd_index++;
		close(err->fd[1]);
		if (err->cmd_index > 1)
			close(err->previous_fd);
		else if (err->cmd_index == err->cmd_nb)
			close(err->previous_fd);
		err->previous_fd = err->fd[0];
		i++;
	}
	return (id);
}

//couper une ligne pour la norme (maybe externaliser les closes en divisant free_close en 2 ?
void	child_process(t_err *err, char *infile, char *outfile, char **env)
{
	char	*path;

	if (err->cmd_index == 0 && !err->heredoc)
	{
		err->previous_fd = open(infile, O_RDONLY);
		error_exit(err->previous_fd, -1, error_msg(err, "open infile failed "), err);
	}
	error_exit(dup2(err->previous_fd, STDIN_FILENO), -1, error_msg(err, "input redirection dup2 failed failed "), err);
	if (err->cmd_index == err->cmd_nb)
	{
		if (err->heredoc)
			err->fd[1] = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			err->fd[1] = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		error_exit(err->fd[1], -1, error_msg(err, "open outfile failed "), err);
	}
	error_exit(dup2(err->fd[1], STDOUT_FILENO), -1, error_msg(err, "output redirection dup2 failed "), err);
	path = handle_cmd(err->cmds[err->cmd_index][0], env, err);
	closing(err);
	if (execve(path, err->cmds[err->cmd_index], env))
	{
		free(path);
		error_exit(-1, -1, error_msg(err, "exexcve failed "), err);
	}
}