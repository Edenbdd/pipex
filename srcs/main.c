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

int main(int argc, char **argv, char **env)
{
    char    ***cmds;
    int     id;
    int     id2;
    int     fd[2];

	if (!env[0])
		env = NULL;
    if (argc != 5)
		return (1);
	cmds = NULL; //faire une fonction initialiser
	fd[0] = 0;
	fd[1] = 0;
    cmds = get_cmds(argv, argc, fd, cmds);
	printf("should not print\n");
	check_access(argv[1], argv[argc - 1], fd, cmds);
    error_exit(pipe(fd), -1, "pipe", 1, fd, cmds);
    id = fork();
    error_exit(id, -1, "first fork", 1, fd, cmds);
    if (id == 0)
		first_child(fd, cmds, argv[1], env);
    id2 = fork();
	error_exit(id, -1, "second fork", 1, fd, cmds);
    if (id2 == 0)
		sec_child(fd, cmds, argv[argc - 1], env);
	free_close(fd, cmds);
    return (waiting(id, id2));
}

/* debug function to print the command
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