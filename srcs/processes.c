/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:48:25 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/09 16:58:35 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//2 functions that each gather all the children specific instructions
//and one function (free_close) for the parent specific instructions
//at the end of the main

#include "pipex.h"

void first_child(int *fd, char **cmd, char *infile, char **env)
{
    int in_fd;
    char *path;

    close(fd[0]);  // Close the reading side of the pipe in the first child
    in_fd = open(infile, O_RDONLY);
    if (in_fd == -1) {
        perror("Error opening infile");
        exit(1);
    }
    printf("%d, STDIN_FILENO is %d\n", in_fd, STDIN_FILENO);
    dup2(in_fd, STDIN_FILENO);
    if (dup2(fd[1], STDOUT_FILENO) == -1) {
        perror("Error with dup2 for stdout");
        exit(1);
    }
    printf("Until here all good 2\n");
    path = handle_cmd(cmd[0]);
    printf("Same bro\n");

    execve(path, cmd, env);
    // If execve fails, print error
    perror("Execve failed in first child");
    exit(1);
}

void sec_child(int *fd, char **cmd, char *outfile, char **env)
{
    int out_fd;
    char *path;

    close(fd[1]);  // Close the writing side of the pipe in the second child
    dup2(fd[0], STDIN_FILENO);
    out_fd = open(outfile, O_WRONLY);
    if (out_fd == -1) {
        perror("Error opening outfile");
        exit(1);
    }
    printf("I guess it is stuck here too?\n");
    dup2(out_fd, STDOUT_FILENO);
    printf("never gonna print until debug\n");
    path = handle_cmd(cmd[0]);
    printf("I'm going to get killed\n");

    execve(path, cmd, env);
    // If execve fails, print error
    perror("Execve failed in second child");
    exit(1);
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