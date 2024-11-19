/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:23:17 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/19 18:03:18 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// functions to handle exit codes, errors, no env...etc

#include "libft.h"
#include "../includes_bonus/pipex_bonus.h"

char	*error_msg(t_err *err, char *msg)
{
	char	*error_msg;
	char	*nb;
	char	*tmp;

	nb = ft_itoa(err->cmd_index);
	tmp = ft_strjoin(msg, nb);
	error_msg = ft_strjoin(tmp, " : ");
	free(tmp);
	free(nb);
	return (error_msg);
}

void	error_exit(int result, int error_return, char *error_msg, t_err *err)
{
	if (!error_msg)
	{
		ft_putstr_fd("error_msg failed ", 2);
		exit(1);
	}
	if (result == error_return)
	{
		ft_putstr_fd(error_msg, 2);
		if (errno != 0)
			perror(NULL);
		else
			ft_putstr_fd("\n", 2);
		free_close(err);
		free(error_msg);
		exit(1);
	}
	free(error_msg);
	return ;
}