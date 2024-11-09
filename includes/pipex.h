/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 09:09:05 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/09 12:08:46 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h> //only for debug delete afterwards
#include <sys/wait.h>
#include <errno.h>

void	check_access(char *infile, char* outfile);
void	first_chid(int *fd, char *infile, char **env);
void	sec_child(int *fd, char *outfile, char **env);
void	free_close(int *fd, char **cmds);

char	**ft_modified_split(const char *str, char c);

char	***get_cmds(char **argv, int argc);