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

#include "../includes/pipex.h"
#include "libft.h"

int	main(int argc, char **argv, char **env)
{
	(void)env;
	char	***cmds;
	int		id;
	int		fd[2];
	//THIS IS PARSING
	if (argc != 5) //for bonus only check that it is >= 5
	{
		printf("Nb of arg is not 4\n");
		return (1);
	}
	check_access(argv[1], argv[argc - 1]);
	cmds = get_cmds(argv, argc);
	print_cmd(cmds); //only for debug
	//THIS IS PIPE, for bonus I need first, middle child (loop) and last child
	pipe(fd);
	id = fork();
	if (id == 0) //first child
		first_child(fd, argv[1], env);
	wait(NULL); //change into waitpid
	id = fork(); //using the same id bcs first child is dead when the second one is born
	if (id == 0) //second child
		sec_child(fd, argv[argc - 1], env);
	wait(NULL); //change into waitpid
	if (id != 0)
		free_close(fd, cmds);
	return (0);
}

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