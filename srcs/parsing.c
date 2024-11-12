/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 09:12:10 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/12 14:30:48 by aubertra         ###   ########.fr       */
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
			perror(NULL);
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
		perror(NULL);
		exit(1);
	}
	if (access(infile, R_OK))
	{
		perror(NULL);
		exit(1);
	}
	if (access(outfile, F_OK))
	{
		perror(NULL);
		exit(1);
	}
	if (access(outfile, W_OK))
	{
		perror(NULL);
		exit(1);
	}
	else
	{
	//	ft_putstr_fd("Files all good\n", 1);
		return ;
	}
}

void	waiting(int id1, int id2)
{
	int		status;
	int		status2;

    waitpid(id1, &status, 0);
    waitpid(id2, &status2, 0);
}