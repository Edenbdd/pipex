/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:46:19 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/18 17:14:07 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"
#include "../includes/libft.h"

	//    id = fork();
    // error_exit(id, -1, error_msg(err, "fork failed "), err);
    // if (id == 0)
    //     heredoc_child_process(err, argv[5], env);
    // err->cmd_index = 1;
    // id2 = fork();
    // error_exit(id2, -1, error_msg(err, "fork failed "), err);
	// if (id2 == 0)
	// {
    //     heredoc_child_process(err, argv[5], env);
	// }

int heredoc_exec(char **argv, char **env, t_err *err)
{
    char *current_line;
    int id;

    check_access(NULL, argv[5], err);
	// faire une fonction handle heredoc
    err->previous_fd = open("heredoc_tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
    error_exit(err->previous_fd, -1, error_msg(err, "creation of heredoc_tmp failed "), err);
    current_line = get_next_line(STDIN_FILENO, argv[2]);
	write(err->previous_fd, current_line, ft_strlen(current_line));
	close(err->previous_fd);
    err->previous_fd = open("heredoc_tmp", O_RDWR | O_CREAT, 0644);
    error_exit(pipe(err->fd), -1, error_msg(err, "pipe failed "), err);
	err->heredoc = 1;
	//
    err->cmds = get_cmds(argv, 6, err, 3);
	id = children_generator(argv, env, 6, err);
	free(current_line);
	free_close(err);
    unlink("heredoc_tmp");
	return (waiting(id));
}


