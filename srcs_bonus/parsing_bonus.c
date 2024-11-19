/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 09:12:10 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/19 18:22:37 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// For now here is parsing functions

#include "libft.h"
#include "../includes_bonus/pipex_bonus.h"

char	***get_cmds(char **argv, int argc, t_err *err)
{
	int	i;
	int	j;

	i = err->first_cmd;
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
	if (err->heredoc)
		infile = NULL;
	if (infile)
	{
		error_exit(access(infile, F_OK), -1, error_msg(err, "infile "), err);
		error_exit(access(infile, R_OK), -1, error_msg(err, "infile "), err);
	}
	if (!access(outfile, F_OK))
		error_exit(access(outfile, W_OK), -1, error_msg(err, "outfile "), err);
}
