/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 09:12:10 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/13 12:00:34 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//For now here is parsing functions + main utils function used to shortened
//the main such as error_exit and waiting

#include "pipex.h"
#include "libft.h"

char ***get_cmds(char **argv, int argc, int *fd, char ***cmds)
{
	int		i;
	int		j;

	i = 2;
	j = 0;
	cmds = ft_calloc(sizeof(char **), argc - 1);
	if (!cmds)
		error_exit(1, 1, "cmds error 1", 1, fd, cmds);
	while (i < argc - 1)
	{
		cmds[j] = ft_split(argv[i], 32);
		if (!cmds)
			error_exit(1, 1, "cmds error", 1, fd, cmds);
		i++;
		j++;
	}
	cmds[j] = NULL;
	return (cmds);
}

void	check_access(char *infile, char* outfile, int *fd, char ***cmds)
{
	error_exit(access(infile, F_OK), -1,"infile", errno, fd, cmds);
	error_exit(access(infile, R_OK), -1,"infile", errno, fd, cmds);
	if (!access(outfile, F_OK))
		error_exit(access(outfile, W_OK), -1, "outfile", errno, fd, cmds);
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