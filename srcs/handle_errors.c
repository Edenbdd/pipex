/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:23:17 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/12 17:10:14 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//functions to handle exit codes, errors, no env...etc

#include "pipex.h"

void	error_exit(int result, int error_code, char *error_msg, int code, int *fd, char ***cmds)
{
	if (result == error_code)
	{
		perror(error_msg);
		free_close(fd, cmds);	
		exit(code);
	}
	else
		return;
}
