/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 09:09:05 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/13 13:50:06 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h> //only for debug delete afterwards
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct s_err		t_err;

struct	s_err
{
	int		*fd;
	char	***cmds;
};

void	check_access(char *infile, char* outfile, t_err *err);
void	first_child(t_err *err, char *infile, char **env);
void	sec_child(t_err *err, char *outfile, char **env);
void	free_close(t_err *err);
void	error_exit(int result, int error_return, char *error_msg, t_err *err);
int		waiting(int id1, int id2);
void	triple_free(char *path, char *tmp, char *to_test);

char	*absolute_path(char *cmd, t_err *err, char *err_msg);
char	*handle_cmd(char *cmd, char **env, t_err *err, char *err_msg);
char	*test_path(char **paths, char *cmd, t_err *err, char *err_msg);

char ***get_cmds(char **argv, int argc, t_err *err);