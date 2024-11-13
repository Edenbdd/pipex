/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 09:09:05 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/13 10:26:24 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h> //only for debug delete afterwards
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>

void	check_access(char *infile, char* outfile, int *fd, char ***cmds);
void	first_child(int *fd, char ***cmds, char *infile, char **env);
void	sec_child(int *fd, char ***cmds, char *outfile, char **env);
void	free_close(int *fd, char ***cmds);
void	error_exit(int result, int error_return, char *error_msg, 
					int errno_code, int *fd, char ***cmds);
void	waiting(int id1, int id2);
void	triple_free(char *path, char *tmp, char *to_test);

char	*absolute_path(char *cmd, int *fd, char ***cmds, char *err_msg);
char	*handle_cmd(char *cmd, char **env, char ***cmds, int *fd, char *err_msg);
char	*test_path(char **paths, char *cmd, char *right_path,
					int *fd, char ***cmds, char *err_msg);

char ***get_cmds(char **argv, int argc, int *fd, char ***cmds);