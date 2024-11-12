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

int main(int argc, char **argv, char **env)
{
    char    ***cmds;
    int     id;
    int     id2;
    int     fd[2];

    if (argc != 5)
    {
        printf("Nb of arg is not 4\n");
        return (1);
    }
    check_access(argv[1], argv[argc - 1]);
    cmds = get_cmds(argv, argc);
	print_cmd(cmds);
    error_exit(pipe(fd), -1, "pipe");
    id = fork();
    error_exit(id, -1, "fork 1");
    if (id == 0)
		first_child(fd, cmds[0], argv[1], env);
    id2 = fork();
	error_exit(id, -1, "fork 2");
    if (id2 == 0)
		sec_child(fd, cmds[1], argv[argc - 1], env);
	free_close(fd, cmds);
	waiting(id, id2);
    return (0);
}
