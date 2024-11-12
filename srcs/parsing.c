/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 09:12:10 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/12 12:57:27 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//For now here is parsing functions + main utils function used to shortened
//the main such as error_exit and waiting

#include "../includes/pipex.h"
#include "../includes/libft.h"

char ***get_cmds(char **argv, int argc)
{
	int		i;
	int		j;
	char	***cmds;

	i = 2;
	j = 0;
	cmds = ft_calloc(sizeof(char **), argc - 1);
	while (i < argc - 1)
	{
		cmds[j] = ft_split(argv[i], 32); //switch this to a better modified split later
		if (!cmds)
		{
			perror("Ft_split or ft_calloc fails in get_cmds\n");
			exit(1);
		}
		i++;
		j++;
	}
	cmds[j] = NULL;
	return (cmds);
}

void	check_access(char *infile, char* outfile)
{
	if (access(infile, F_OK))
	{
		perror("Infile doesn't exists\n");
		exit(1);
	}
	if (access(infile, R_OK))
	{
		perror("Infile permission denied");
		exit(1);
	}
	if (access(outfile, F_OK))
	{
		perror("Outfile doesn't exists\n");
		exit(1);
	}
	if (access(outfile, W_OK))
	{
		perror("Outfile permission denied");
		exit(1);
	}
	else
	{
		ft_putstr_fd("Files all good\n", 1);
		return ;
	}
}

void	error_exit(int result, int error_code, char *error_msg)
{
	if (result == error_code)
	{
		perror(error_msg);
		exit(1);
	}
	else
		return;
}

void	waiting(int id1, int id2)
{
	int		status;
	int		status2;

    waitpid(id1, &status, 0);
    waitpid(id2, &status2, 0);
}