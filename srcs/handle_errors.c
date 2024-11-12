/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:23:17 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/12 14:24:53 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//functions to handle exit codes, errors, no env...etc

#include "pipex.h"

void	error_exit(int result, int error_code, char *error_msg, int code)
{
	if (result == error_code)
	{
		perror(error_msg);
		exit(code);
	}
	else
		return;
}
