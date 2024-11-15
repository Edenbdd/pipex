/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 09:12:10 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/15 17:44:59 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// For now here is parsing functions + main utils function used to shortened
// the main such as error_exit and waiting

#include "../includes/libft.h"
#include "../includes_bonus/pipex_bonus.h"

char	***get_cmds(char **argv, int argc, t_err *err)
{
	int	i;
	int	j;
	char	*error_nb;

	i = 2;
	j = 0;
	err->cmds = ft_calloc(sizeof(char **), argc - 1);
	if (!err->cmds)
		error_exit(1, 1, error_msg(err, "ft_calloc failed in get_cmds "), err);
	while (i < argc - 1)
	{
		err->cmds[j] = ft_split(argv[i], 32);
		if (!err->cmds)
			error_exit(1, 1, error_msg(err, "split error in cmds "), err);
		i++;
		j++;
	}
	err->cmds[j] = NULL;
	return (err->cmds);
}

void	check_access(char *infile, char *outfile, t_err *err)
{
	error_exit(access(infile, F_OK), -1, error_msg(err, "infile "), err);
	error_exit(access(infile, R_OK), -1, error_msg(err, "infile "), err);
	if (!access(outfile, F_OK))
		error_exit(access(outfile, W_OK), -1, error_msg(err, "outfile "), err);
}

int	waiting(int id_last)
{
	int	status;
	int	retcode;

	while (ECHILD != errno)
	{
		if (waitpid(0, &status, 0) == id_last)
		{
			if (WIFEXITED(status))
				retcode = WEXITSTATUS(status);
			else
				retcode = WSTOPSIG(status);
		}
	}
	printf("not gonna print\n");
	return (retcode);
}
