/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:46:07 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/09 09:10:12 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Main + helper functions

#include "libft.h"
#include "../includes_bonus/pipex_bonus.h"

void	init(t_err *err, int argc)
{
	err->first_cmd = 2;
	err->heredoc = 0;
	err->cmd_index = 0;
	err->fd[0] = -1;
	err->fd[1] = -1;
	err->previous_fd = -1;
	err->cmd_nb =  argc - 4;
	err->cmds = NULL;
}

void	create_doc(char **argv, t_err *err)
{
	char *current_line;
	if (!access("heredoc_tmp", F_OK))
	{
		if (access("heredoc_tmp", R_OK | W_OK))
		{
			error_exit(-1, -1, error_msg(err, 
			"heredoc_tmp already exists without read & write permissions : "), err);
		}
	}	
	err->previous_fd = open("heredoc_tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
    error_exit(err->previous_fd, 4, error_msg(err, "creation of heredoc_tmp failed "), err);
	while (1)
	{
   		current_line = get_next_line(STDIN_FILENO); 
		if (!ft_strncmp(current_line, argv[2], ft_strlen(current_line) - 1))
		{
			free(current_line);
			break;
		}
		write(err->previous_fd, current_line, ft_strlen(current_line));
		free(current_line);
	}
	close(err->previous_fd);
    err->previous_fd = open("heredoc_tmp", O_RDWR | O_CREAT, 0644);
	err->heredoc = 1;
	err->first_cmd = 3;
	err->cmd_nb -= 1;
}


int	main(int argc, char **argv, char **env)
{
	t_err	err;
	int		id;
	
	if (!env[0])
		env = NULL;
	if ((argc < 6 && !ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1]) + 1)) || argc < 5)
	{
		ft_putstr_fd("./pipex infile cmd cmd cmd outfile\n", 2);
		ft_putstr_fd("./pipex here_doc lim cmd cmd outfile\n", 2);
		return (1);
	}
	init(&err, argc);
	if (!ft_strncmp(argv[1], "here_doc", 8))
		create_doc(argv, &err);
	check_access(argv[1], argv[argc - 1], &err);
	err.cmds = get_cmds(argv, argc, &err);
	id = children_generator(argv, env, argc, &err);
	free_close(&err);
	return (waiting(id));
}

int	waiting(int id_last)
{
	int	status;
	int	retcode;

	while (ECHILD != errno)
	{
		if (waitpid(-1, &status, 0) == id_last)
		{
			if (WIFEXITED(status))
				retcode = WEXITSTATUS(status);
			if (WIFSIGNALED(status)) 
			{
				retcode = WTERMSIG(status);
				if (retcode != 131)
					retcode += 128;
			}
		}
	}
	return (retcode);
}