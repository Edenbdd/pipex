/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 09:09:05 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/12 15:21:55 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h> //only for debug delete afterwards
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>

void	check_access(char *infile, char* outfile);
void	first_child(int *fd, char **cmd, char *infile, char **env);
void	sec_child(int *fd, char **cmd, char *outfile, char **env);
void	free_close(int *fd, char ***cmds);
void	error_exit(int result, int error_code, char *error_msg, int code);
void	waiting(int id1, int id2);

char	*handle_cmd(char *cmd);
char	*absolute_path(char *cmd);

char	**ft_modified_split(const char *str, char c);

char	***get_cmds(char **argv, int argc);