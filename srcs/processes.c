/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:48:25 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/12 15:16:36 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//2 functions that each gather all the children specific instructions
//and one function (free_close) for the parent specific instructions
//at the end of the main

#include "pipex.h"

void first_child(int *fd, char **cmd, char *infile, char **env)
{
 	char	*path;
	int		in_fd;

	close(fd[0]);
    in_fd = open(infile, O_RDONLY);
	error_exit(in_fd, -1, NULL, 1);
    dup2(in_fd, STDIN_FILENO);
    close(in_fd);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);
	path = handle_cmd(cmd[0]);
    error_exit(execve(path, cmd, env) , -1, NULL, 1);
}

void sec_child(int *fd, char **cmd, char *outfile, char **env)
{
    char	*path;
	int		out_fd;

    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
    out_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	error_exit(out_fd, -1, NULL, 1);
    dup2(out_fd, STDOUT_FILENO);
    close(out_fd);
    path = handle_cmd(cmd[0]);
    error_exit(execve(path, cmd, env) , -1, NULL, 1);
}

void	free_close(int *fd, char ***cmds)
{
	int	i;
	int	j;

	i = 0;
	close(fd[1]);
	close(fd[0]);
	while (cmds[i])
	{
		j = 0;
		while(cmds[i][j])
		{
			free(cmds[i][j]);
			j++;
		}
		free(cmds[i]);
		i++;
	}
	free(cmds);
}