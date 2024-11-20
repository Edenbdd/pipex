/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 09:12:10 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/20 14:51:48 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// For now here is parsing functions + main utils function used to shortened
// the main such as error_exit and waiting

#include "libft.h"
#include "../includes/pipex.h"

static int	only_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 32)
			return (0);
		i++;
	}
	return (1);
}

char	***get_cmds(char **argv, int argc, t_err *err)
{
	int	i;
	int	j;

	i = 2;
	j = 0;
	while (i < argc - 1)
	{
		if (!argv[i][0] || only_space(argv[i]))
			error_exit(1, 1, "there is an empty cmd", err);
		i++;
	}
	err->cmds = ft_calloc(sizeof(char **), argc - 1);
	if (!err->cmds)
		error_exit(1, 1, "cmds error 1 : ", err);
	i = 2;
	while (i < argc - 1)
	{
		err->cmds[j] = ft_split(argv[i], 32);
		if (!err->cmds)
			error_exit(1, 1, "cmds error : ", err);
		i++;
		j++;
	}
	err->cmds[j] = NULL;
	return (err->cmds);
}

void	check_access(char *infile, char *outfile, t_err *err)
{
	error_exit(access(infile, F_OK), -1, "infile : ", err);
	error_exit(access(infile, R_OK), -1, "infile : ", err);
	if (!access(outfile, F_OK))
		error_exit(access(outfile, W_OK), -1, "outfile : ", err);
}

int	waiting(int id1, int id2)
{
	int	status;
	int	retcode;

	(void)id1;
	while (ECHILD != errno)
	{
		if (waitpid(0, &status, 0) == id2)
		{
			if (WIFEXITED(status))
				retcode = WEXITSTATUS(status);
			else
				retcode = WSTOPSIG(status);
		}
	}
	return (retcode);
}
