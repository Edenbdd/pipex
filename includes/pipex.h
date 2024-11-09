/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 09:09:05 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/09 16:12:00 by aubertra         ###   ########.fr       */
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

//char	*handle_cmd(char ***cmds, char **env);
char	*handle_cmd(char *cmd);

char	**ft_modified_split(const char *str, char c);

char	***get_cmds(char **argv, int argc);