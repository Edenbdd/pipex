/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:48:25 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/09 16:25:57 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//2 functions that each gather all the children specific instructions
//and one function (free_close) for the parent specific instructions
//at the end of the main

#include "pipex.h"

void	first_child(int *fd, char **cmd, char *infile, char **env)
{
	int		in_fd;
	char	*path;

	//here I need to WRITE the output in the pipe & to READ from infile
	close(fd[0]); //fd[0] is to read
	in_fd = open(infile, O_RDONLY);
	printf("before all is good\n");
	dup2(in_fd, STDIN_FILENO);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		perror("here is the mistake\n");
		exit(1);
	}
	printf("Until here all good 2\n");
	path = handle_cmd(cmd[0]);
	printf("Same bro\n");
	execve(path, cmd, env);
	close(fd[1]); //fd[1] is to write->but I need this to write in it with execve? this will not be applied ?
}

void	sec_child(int *fd, char **cmd, char *outfile, char **env)
{
	int		out_fd;
	char	*path;
	//here I need to READ from the pipe & to WRITE to outfile
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	out_fd = open(outfile, O_WRONLY);
	printf("I guess it is stuck here too?\n");
	dup2(out_fd, STDOUT_FILENO);
	printf("never gonna print until debug\n");
	path = handle_cmd(cmd[0]);
	printf("I'm going to get killed\n");
	execve(path, cmd, env);
	close(fd[0]); //but I need this open to read from it with execve? this will not be applied ?
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