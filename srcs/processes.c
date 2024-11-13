/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:48:25 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/13 09:25:51 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//2 functions that each gather all the children specific instructions

#include "pipex.h"

void first_child(int *fd, char ***cmds, char *infile, char **env)
{
 	char	*path;
	int		in_fd;

    in_fd = open(infile, O_RDONLY);
	error_exit(in_fd, -1, NULL, 1 , fd, cmds);
    dup2(in_fd, STDIN_FILENO);
    close(in_fd);
	dup2(fd[1], STDOUT_FILENO);
	path = handle_cmd(cmds[0][0], env, cmds, fd, "first cmd");
	close(fd[0]);
	close(fd[1]);
    error_exit(execve(path, cmds[0], env) , -1, "first exexcve", errno, fd, cmds);
}

void sec_child(int *fd, char ***cmds, char *outfile, char **env)
{
    char	*path;
	int		out_fd;

    dup2(fd[0], STDIN_FILENO);
    out_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644); //check la creation du fichier
	error_exit(out_fd, -1, NULL, 1, fd, cmds);
    dup2(out_fd, STDOUT_FILENO);
    close(out_fd);
    path = handle_cmd(cmds[1][0], env, cmds, fd, "second cmd");
	close(fd[1]);
	close(fd[0]);
    error_exit(execve(path, cmds[1], env) , -1, "second execve", errno, fd, cmds);
}