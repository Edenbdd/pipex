/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:23:17 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/19 12:05:52 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// functions to handle exit codes, errors, no env...etc

#include "../includes/libft.h"
#include "../includes_bonus/pipex_bonus.h"

char	*error_msg(t_err *err, char *msg)
{
	char	*error_msg;
	char	*nb;

	nb = ft_itoa(err->cmd_index);
	error_msg = ft_strjoin(msg, nb);
	free(nb);
	return (error_msg);
}

void	error_exit(int result, int error_return, char *error_msg, t_err *err)
{
	if (!error_msg)
		ft_putstr_fd("error_msg failed", 2);
	if (result == error_return)
	{
		perror(error_msg);
		free(error_msg);
		free_close(err);
		exit(1);
	}
	free(error_msg);
	return ;
}