/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 09:12:10 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/13 10:09:51 by aubertra         ###   ########.fr       */
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
	error_exit(access(outfile, F_OK), -1,"outfile", errno, fd, cmds); //voir creation pour outfile
	error_exit(access(outfile, W_OK), -1,"outfile", errno, fd, cmds);
}

void	waiting(int id1, int id2)
{
	int		status;
	int		status2;

    waitpid(id1, &status, 0);
    waitpid(id2, &status2, 0);
}