/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:23:17 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/13 09:09:51 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//functions to handle exit codes, errors, no env...etc
//and exit without leaks

#include "pipex.h"

void	error_exit(int result, int error_return, char *error_msg, int errno_code, int *fd, char ***cmds)
{
	if (result == error_return)
	{
		perror(error_msg);
		free_close(fd, cmds);	
		exit(errno_code);
	}
	else
		return;
}

void	free_close(int *fd, char ***cmds)
{
	int	i;
	int	j;

	i = 0;
	if (fd)
	{
		if (fd[0])
			close(fd[1]);
		if(fd[0])	
			close(fd[0]);
	}
	while (cmds[i])
	{
		j = 0;
		while(cmds[i][j])
		{
			free(cmds[i][j]);
			j++;
		}
		free(cmds[i]);
		i++;
	}
	free(cmds);
}