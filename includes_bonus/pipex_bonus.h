/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 09:09:05 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/18 09:53:25 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_err	t_err;

struct					s_err
{
	int					cmd_index;
	int					cmd_nb;
	int					previous_fd;
	int					fd[2];
	char				***cmds;
};

void					free_heredoc(t_err *err, char *current_line);
void					check_access(char *infile, char *outfile, t_err *err);
void					child_process(t_err *err, char *infile, char *outfile, char **env);
void					free_close(t_err *err);
void					error_exit(int result, int error_return,
							char *error_msg, t_err *err);
void					triple_free(char *path, char *tmp, char *to_test);
void					free_cmds(t_err *err);
void					free_path(char **paths);
void					heredoc_child_process(t_err *err, char *outfile, char **env);

int						heredoc_exec(char **argv, char **env, t_err *err);
int						waiting(int id_last);

char					*absolute_path(char *cmd, t_err *err);
char					*handle_cmd(char *cmd, char **env, t_err *err);
char					*test_path(char **paths, char *cmd, t_err *err);
char					*join_path(char *path, char *cmd, t_err *err,
							char **paths);
char					*error_msg(t_err *err, char *msg);

char					***get_cmds(char **argv, int argc, t_err *err, int first_cmd_index);

#endif