/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 09:12:10 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/20 14:58:25 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// For now here is parsing functions

#include "libft.h"
#include "../includes_bonus/pipex_bonus.h"

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

	i = err->first_cmd;
	j = 0;
	while (i < argc - 1)
	{
		if (!argv[i][0] || only_space(argv[i]))
			error_exit(1, 1, error_msg(err, "there is an empty cmd "), err);
		i++;
	}
	err->cmds = ft_calloc(sizeof(char **), argc - 1);
	if (!err->cmds)
		error_exit(1, 1, error_msg(err, "ft_calloc fails in get_cmds "), err);
	i = err->first_cmd;
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
