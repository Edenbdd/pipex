/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:48:25 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/09 12:09:14 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//2 functions that each gather all the children specific instructions
//and one function (free_close) for the parent specific instructions
//at the end of the main

void	first_chid(int *fd, char *infile, char **env)
{
	close(fd[0]); //fd[0] is to read
	close(fd[1]); //fd[1] is to write
	return (0);
}

void	sec_child(int *fd, char *outfile, char **env)
{
	close(fd[1]);
	close(fd[0]);
	return (0);
}

void	free_close(int *fd, char **cmds)
{
	close(fd[1]);
	close(fd[0]);
	free(cmds);
}