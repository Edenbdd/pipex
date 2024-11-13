/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:46:07 by aubertra          #+#    #+#             */
/*   Updated: 2024/11/09 09:10:12 by aubertra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Only the main here

#include "pipex.h"
#include "libft.h"
/*
static void	print_cmd(char ***cmds) //just for debug, delete/command at the end
{
	int	i;
	int	j;

	i = 0;
	while (cmds[i])
	{
		j= 0;
		while (cmds[i][j])
		{
			printf("%s;", cmds[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}
*/
int main(int argc, char **argv, char **env)
{
    char    ***cmds;
    int     id;
    int     id2;
    int     fd[2];

	if (!env[0])
		env = NULL;
	//check nb arg
    if (argc != 5)
		{return (1);}
    //check files
	check_access(argv[1], argv[argc - 1]);
	//cmds
    cmds = get_cmds(argv, argc);
//	print_cmd(cmds); pour debug si besoin
    error_exit(pipe(fd), -1, NULL, 1, fd, cmds);
    id = fork();
    error_exit(id, -1, NULL, 1, fd, cmds);
    if (id == 0)
		first_child(fd, cmds, argv[1], env);
    id2 = fork();
	error_exit(id, -1, NULL, 1, fd, cmds);
    if (id2 == 0)
		sec_child(fd, cmds, argv[argc - 1], env);
	free_close(fd, cmds);
	waiting(id, 0);
    return (0);
}
