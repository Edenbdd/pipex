/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:48:25 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/16 16:46:13 by aubertra         ###   ########.fr       */
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

//mettre ca dans un fichier a part 
int heredoc_exec(char **argv, char **env, t_err *err)
{
    char *current_line;
    int id;
    int id2;

    check_access(NULL, argv[5], err); // Check if outfile exists and that we have permission to write in it
    err->previous_fd = open("heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    error_exit(err->previous_fd, -1, error_msg(err, "creation of heredoc_tmp failed "), err);
    // Read the first line of input from stdin (until the limiter)
    current_line = get_next_line(STDIN_FILENO, argv[2]);
    printf("get next line is done !\nlets print current_line: {%s}\n", current_line);
    // Write it to the temporary file
    write(err->previous_fd, current_line, ft_strlen(current_line));
    free(current_line);
    err->cmds = get_cmds(argv, 6, err, 3);
    error_exit(pipe(err->fd), -1, error_msg(err, "pipe failed "), err); // One pipe for communication
    id = fork(); // Fork for the first command
    error_exit(id, -1, error_msg(err, "fork failed "), err);
    if (id == 0)
    {
        // First child process: handle heredoc and execute command
        heredoc_child_process(err, argv[5], env);
    }
    err->cmd_index = 1;
    id2 = fork(); // Fork for the second command
    error_exit(id2, -1, error_msg(err, "fork failed "), err);
    if (id2 == 0)
    {
        // Second child process: handle input/output redirection and execute command
        heredoc_child_process(err, argv[5], env);
    }
    free_close(err);
    return (waiting(id2));
}

void heredoc_child_process(t_err *err, char *outfile, char **env)
{
    char *path;
    int fd_out;

    // Input redirection (from heredoc_tmp or pipe)
    if (err->cmd_index == 0)
    {
		printf("first i come here\n");
        // First child: input comes from the heredoc_tmp file
        dup2(err->previous_fd, STDIN_FILENO);
    }
    else
    {
		printf("second i come here\n");
        // Second child: input comes from the pipe
        dup2(err->fd[0], STDIN_FILENO);
    }
    // Close file descriptors after duplicating them
    close(err->previous_fd);
    close(err->fd[0]);
    // Output redirection
    if (err->cmd_index == 1)
    {
		printf("fourht i come here\n");
        // If it's the second command, redirect to outfile
        fd_out = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
        error_exit(fd_out, -1, error_msg(err, "open outfile failed "), err);
        dup2(fd_out, STDOUT_FILENO);
        close(fd_out);
    }
    else
    {
		printf("third i come here\n");
        // If it's the first command, output goes to the pipe
        dup2(err->fd[1], STDOUT_FILENO);
        close(err->fd[1]);
    }
    // Execute the command
    path = handle_cmd(err->cmds[err->cmd_index][0], env, err);
    if (execve(path, err->cmds[err->cmd_index], env))
    {
        free(path);
        error_exit(-1, -1, error_msg(err, "execve failed "), err);
    }
}

