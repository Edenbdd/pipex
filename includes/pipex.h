/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 09:09:05 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/20 11:50:47 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_err	t_err;

struct					s_err
{
	int					*fd;
	char				***cmds;
};

void					check_access(char *infile, char *outfile, t_err *err);
void					first_child(t_err *err, char *infile, char **env);
void					sec_child(t_err *err, char *outfile, char **env);
void					free_close(t_err *err);
void					error_exit(int result, int error_return,
							char *error_msg, t_err *err);
void					free_cmds(t_err *err);
void					free_path(char **paths);

int						waiting(int id1, int id2);

char					*absolute_path(char *cmd, t_err *err, char *err_msg);
char					*handle_cmd(char *cmd, char **env, t_err *err,
							char *err_msg);
char					*test_path(char **paths, char *cmd, t_err *err,
							char *err_msg);
char					*join_path(char *path, char *cmd, t_err *err,
							char **paths);
char					*ft_getenv(char **env);

char					***get_cmds(char **argv, int argc, t_err *err);

#endif