/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 09:12:10 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/09 11:48:31 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "libft.h"

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
			perror("Ft_modified_split or ft_calloc fails in get_cmds\n");
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